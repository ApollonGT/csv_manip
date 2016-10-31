#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;

static void write_new_line(ofstream &output_file, vector<string> fields)
{
    string new_line;
    for (int i = 0; i < fields.size(); i++) {
        new_line.append(fields.at(i));
        new_line.append(",");
    }

    size_t last_comma = new_line.find_last_of(",");
    new_line.replace(last_comma, 1, "\n");

    output_file << new_line;

} // write_new_line

static void convert_date_format(vector<string> &fields, int field)
{
    string old_date = fields.at(field);
    std::tm od;
    strptime(old_date.c_str(), "%d/%m/%Y", &od);

    char buffer[256];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &od);

    string new_time(buffer);

    fields.at(field) = new_time;
} // convert_date_format

static void convert_csv_date_format(ifstream &input_file, string filename, int field)
{
        string new_filename = string(filename);

        size_t last_dot = new_filename.find_last_of(".");
        new_filename.replace(last_dot, 1, "_new.");

        ofstream output_file(new_filename, ofstream::out);

        cout << "converting dates in " << filename << " field " << field << "." << endl;
        cout << "New Filename: " << new_filename << endl;

        string line;
        vector<string> fields;
        char delimiter = ',';
        while (getline(input_file, line)) {
            stringstream ss(line);
            string tok;

            while (getline(ss, tok, delimiter)) {
                 fields.push_back(tok);
            }

            convert_date_format(fields, field);
            write_new_line(output_file, fields);

            fields.clear();
        }

        output_file.close();

} // convert_csv_date_format

int main(int argc, char const* argv[])
{
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " -i <filename.csv> -f <field>" << endl;
        return 1;
    }

    if (string(argv[1]) == "-i" && string(argv[3]) == "-f") {
        string filename = string(argv[2]);
        string s_field = string(argv[4]);
        int field;
        try {
            field = stoi(s_field);
        } catch (const invalid_argument& ia) {
            cerr << "Invalid argument: field number must be integer (" << s_field << ")" << endl;
            return 1;
        }

        if (filename.find_last_of(".csv") == string::npos) {
             cerr << "Supported filenames: <filename>.csv" << endl;
             return 1;
        }

        ifstream input_file(filename);

        if (!input_file.is_open()) {
             cerr << "Unable to open file '" << filename << "'. Check if file exists and if you have the right permissions." << endl;
             return 1;
        }

        convert_csv_date_format(input_file, filename, field);

        input_file.close();
    } else {
        cerr << "Invalid parameters." << endl << "Usage: " << argv[0] << " -i <filename.csv> -f <field>" << endl;
        return 1;
    }

    return 0;
}
