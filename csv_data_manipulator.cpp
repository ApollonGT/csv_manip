// System headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
// --------------

#include "csv_data_manipulator.hpp"

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

CSVData::CSVData(string filename) :
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

void CSVData::delete_row(int row)
{
	if (row >= m_rows || row < 0) return;
	m_data.erase(m_data.begin() + row);
	m_rows--;
	m_is_modified = true;
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

void CSVData::read_file(string filename)
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
        stringstream ss(line);
        string tok;
        vector<string> row;

        while (getline(ss, tok, CSV_DELIMITER)) {
            row.push_back(tok);
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

void CSVData::write_data(string filename)
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

void CSVData::convert_date_format(string old_format, string new_format, int column)
{
    for (int row = 0; row < m_data.size(); ++row) convert_date_format(old_format, new_format, row, column);
}

// ----------------------------------------------------------------------------------------------------------|

void CSVData::convert_date_format(string old_format, string new_format, int row, int column)
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
