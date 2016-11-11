#include <iostream>
#include <stdexcept>

#include "../csv_data_manipulator.hpp"

using namespace std;

int valid_arguments(int argc, char const* argv[], int &field)
{
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " -i <filename.csv> -f <field>" << endl;
        return 0;
    }

    if (string(argv[1]) == "-i" && string(argv[3]) == "-f") {
        string filename = string(argv[2]);
        string s_field = string(argv[4]);
        try {
            field = stoi(s_field);
        } catch (const invalid_argument& ia) {
            cerr << "Invalid argument: field number must be integer (" << s_field << ")" << endl;
            return 0;
        }

        if (filename.find_last_of(".csv") == string::npos) {
             cerr << "Supported filenames: <filename>.csv" << endl;
             return 0;
        }
    } else {
        cerr << "Invalid parameters." << endl << "Usage: " << argv[0] << " -i <filename.csv> -f <field>" << endl;
        return 0;
    }

    return 1;
}

int main(int argc, char const* argv[])
{
    int field;
    if (!valid_arguments(argc, argv, field)) return 1;

    string filename = string(argv[2]);

    CSVData csv_data(filename);

    csv_data.convert_date_format("%d/%m/%Y", "%Y-%m-%d", field);

    string new_filename = string(filename);
    size_t last_dot = new_filename.find_last_of(".");
    new_filename.replace(last_dot, 1, "_new.");

    csv_data.write_data(new_filename);

    return 0;
}
