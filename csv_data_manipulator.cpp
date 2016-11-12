// System headers
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
// --------------

#include "csv_data_manipulator.hpp"

#define C_STRING_DELIMITER '"'
#define S_STRING_DELIMITER "\""
#define TMP_DELIM_REPLACEMENT "#|#"

using namespace std;

// ==========================================================================================================|

CSVData::CSVData() : m_is_modified(false), m_is_unified(true), m_rows(0), m_cols(0)
{
}

// ----------------------------------------------------------------------------------------------------------|

CSVData::CSVData(CSVData &rhs) :
    m_is_modified(rhs.is_modified()), m_is_unified(rhs.is_unified()),
    m_rows(rhs.m_rows), m_cols(rhs.m_cols)
{
}

// ----------------------------------------------------------------------------------------------------------|

CSVData::CSVData(const string &filename) :
    m_is_modified(false), m_is_unified(true), m_rows(0), m_cols(0)
{
    read_file(filename);
    m_is_modified = false;
}

// ----------------------------------------------------------------------------------------------------------|

const string CSVData::get_value(int row, int col)
{
     if (row >= m_rows || col >= m_cols) return "";
     return const_cast<string&>(m_data.at(row).at(col));
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::set_value(int row, int col, string value)
{
     if (row >= m_rows || col >= m_cols) return;

     m_data.at(row).at(col) = value;
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::add_row(vector<string> row_data)
{
     size_t new_row_size = row_data.size();
     if (new_row_size != m_cols && m_is_unified) m_is_unified = false;
     m_data.push_back(row_data);
     m_rows++;
     if (m_cols < new_row_size) m_cols = new_row_size;
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::add_row(vector<string> row_data, int pos)
{
     if (pos < 0 || pos >= m_data.size()) return;

     vector< vector<string> >::iterator it = m_data.begin() + pos;

     size_t new_row_size = row_data.size();
     if (new_row_size != m_cols && m_is_unified) m_is_unified = false;

     m_data.insert(it, row_data);
     m_rows++;
     if (m_cols < new_row_size) m_cols = new_row_size;
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::delete_row(int row)
{
	if (row >= m_rows || row < 0) return;
	m_data.erase(m_data.begin() + row);
	m_rows--;
	m_is_modified = true;
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::delete_row_if(function<bool(int, int, const std::string&)> cbFun)
{
    vector<int> rows_to_delete;

    for (int row = 0; row < m_data.size(); ++row) {
        for (int col = 0; col < m_data.at(row).size(); ++col) {
            if ( cbFun(row, col, m_data.at(row).at(col)) ) {
                rows_to_delete.push_back(row);
                break;
            }
        }
    }

    if (rows_to_delete.size() > 0) {
        sort(rows_to_delete.begin(), rows_to_delete.end(), std::greater<int>());
        for (int row = 0; row < rows_to_delete.size(); ++row) delete_row(rows_to_delete.at(row));
    }
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::delete_col(int col)
{
	if (col >= m_cols || col < 0) return;
	for (int i = 0; i < m_data.size(); ++i) {
		if (col < m_data.at(i).size()) {
			m_data.at(i).erase(m_data.at(i).begin() + col);
			m_is_modified = true;
			m_is_unified = false;
		}
	}
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::delete_item(int row, int col)
{
	if (row >= m_rows || row < 0) return;
	if (col >= m_data.at(row).size() || col < 0) return;

	m_data.at(row).erase(m_data.at(row).begin() + col);
	m_is_modified = true;
	m_is_unified = false;
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::read_file(const string &filename)
{
    ifstream input_file(filename.c_str());

    if (!input_file.is_open()) {
        cerr << "Unable to open file '" << filename << "'. Check if file exists and if you have the right permissions." << endl;
        return;
    }

    m_data.clear();
    string line;

    int cols = 0;
    while (getline(input_file, line)) {
        int contains_strings = 0;
        if ( (contains_strings = count(line.begin(), line.end(), C_STRING_DELIMITER)) > 0 ) {
            size_t left = line.find(C_STRING_DELIMITER, 0);
            size_t right = line.find(C_STRING_DELIMITER, left + 1);

            while (left != string::npos && right != string::npos) {
                size_t found = left;
                while (true) {
                    found = line.find(C_STRING_DELIMITER, found);
                    if (found == string::npos) break;

                    line.replace(found, 1, TMP_DELIM_REPLACEMENT);
                    found += 3;
                }

                left = line.find(C_STRING_DELIMITER, right);
                right = line.find(C_STRING_DELIMITER, left + 1);
            }
        }

        stringstream ss(line);
        string tok, i_row;
        vector<string> row;

        while (getline(ss, tok, CSV_DELIMITER)) {
            if (tok.find(TMP_DELIM_REPLACEMENT) != string::npos) {
                i_row = tok;

                size_t found = 0;
                while (true) {
                    found = i_row.find(TMP_DELIM_REPLACEMENT, found);
                    if (found == string::npos) break;

                    i_row.replace(found, 3, string(S_STRING_DELIMITER));
                    found++;
                }
            } else {
                i_row = tok;
            }
            row.push_back(i_row);
        }

        if (cols != 0 && cols != row.size()) m_is_unified = false;

        cols = row.size();

        m_data.push_back(row);
    }

    input_file.close();

    m_is_modified = true;
    m_cols = cols;
    m_rows = m_data.size();
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::write_data(const string &filename)
{
    ofstream output_file(filename.c_str(), ofstream::out);

    for (int row = 0; row < m_data.size(); ++row) {
        string new_line;

        vector<string> row_data = m_data.at(row);
        for (int i = 0; i < row_data.size(); i++) {
            new_line.append(row_data.at(i));
            new_line.append(",");
        }

        size_t last_comma = new_line.find_last_of(",");
        new_line.replace(last_comma, 1, "\n");

        output_file << new_line;
    }

    output_file.close();

    m_is_modified = false;
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::convert_date_format(const std::string &old_format, const std::string &new_format, int column)
{
    for (int row = 0; row < m_data.size(); ++row) convert_date_format(old_format, new_format, row, column);
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::convert_date_format(const std::string &old_format, const std::string &new_format, int row, int column)
{
    if (column >= m_cols) {
        cerr << "Invalid column number: " << column << endl;
        return;
    }

    if (row >= m_rows) {
        cerr << "Invalid row number: " << row << endl;
        return;
    }

    vector<string> row_data = m_data.at(row);

    string old_date = row_data.at(column);
    std::tm od;
    strptime(old_date.c_str(), old_format.c_str(), &od);

    char buffer[256];
    strftime(buffer, sizeof(buffer), new_format.c_str(), &od);

    string new_date(buffer);

    m_data.at(row).at(column) = new_date;

    m_is_modified = true;
}

// ==========================================================================================================|
