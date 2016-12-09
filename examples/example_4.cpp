#include <iostream>

#include "../csv_data_manipulator.hpp"

using namespace std;

int valid_arguments(int argc, char const* argv[])
{
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " -i <filename.csv> -a <filename>.csv" << endl;
        return 0;
    }

    if (string(argv[1]) == "-i" && string(argv[3]) == "-a") {
        string filename1 = string(argv[2]);
        string filename2 = string(argv[4]);
        if (filename1.find_last_of(".csv") == string::npos || filename2.find_last_of(".csv") == string::npos) {
             cerr << "Supported filenames: <filename>.csv" << endl;
             return 0;
        }
    } else {
        cerr << "Invalid parameters." << endl << "Usage: " << argv[0] << " -i <filename.csv> -a <filename>.csv" << endl;
        return 0;
    }

    return 1;
}

int main(int argc, char const* argv[])
{
    if (!valid_arguments(argc, argv)) return 1;

    string filename1 = string(argv[2]);
    string filename2 = string(argv[4]);

    CSVData csv_data(filename1);

    csv_data.append_file(filename2);

    string new_filename = string("example_4_data_new.csv");

    csv_data.write_data(new_filename);

    return 0;
}
