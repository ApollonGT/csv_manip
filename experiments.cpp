/* EXPERIMENTATION
 *
 * This file contains the main function for user experimentation.
 */
#include <iostream>
//#include <stdexcept> // try{}catch{}

#include "csv_data_manipulator.hpp"

using namespace std;

int main(int argc, char const* argv[])
{
    /*  Experiment here */

    string filename("examples/csv_10000_lines.csv");
    string new_filename("examples/csv_10000_lines_new.csv");

    CSVData csv_data(filename);

    csv_data.write_data(new_filename);

    return 0;
}
