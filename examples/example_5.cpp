#include <iostream>
#include "../csv_data_manipulator.hpp"

using namespace std;

int main(int argc, char const* argv[])
{
    string filename("example_5_data.csv");
    string new_filename("example_5_data_new.csv");

    CSVData csv_data(filename);
    csv_data.make_data_unique();
    csv_data.sort_by_col(0, CSVData::ASC);
    csv_data.write_data(new_filename);

    return 0;
}
