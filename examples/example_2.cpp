#include <iostream>
#include "../csv_data_manipulator.hpp"

using namespace std;

int valid_arguments(int argc, char const* argv[])
{
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " -i <filename>.csv" << endl;
        return 0;
    }

    if (string(argv[1]) == "-i") {
        string filename = string(argv[2]);

        if (filename.find_last_of(".csv") == string::npos) {
             cerr << "Supported filenames: <filename>.csv" << endl;
             return 0;
        }
    } else {
        cerr << "Invalid parameters." << endl << "Usage: " << argv[0] << " -i <filename.csv>" << endl;
        return 0;
    }

    return 1;
}

bool id_is_even(int row, int col, const string &val)
{
    int i_val = atoi( val.c_str() );
    if ( col == 0 && i_val > 0 && i_val % 2 == 0 ) return true;
    return false;
}

int main(int argc, char const* argv[])
{
    if (!valid_arguments(argc, argv)) return 1;

    string filename = string(argv[2]);

    CSVData csv_data(filename);

    csv_data.delete_row_if(id_is_even);

    string new_filename = string(filename);
    size_t last_dot = new_filename.find_last_of(".");
    new_filename.replace(last_dot, 1, "_new.");

    csv_data.write_data(new_filename);

    return 0;
}
