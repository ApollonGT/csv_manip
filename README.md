### CSV Data Manipulator

A simple C++ application that reads the data of a ``.csv`` file and provides an api for manipulating and saving these data.

A possible application could be to prepare a ``.csv`` to be imported in a SQLite database.

#### Requirements
* make
* GNU Compiler - g++

To compile just cd into the cloned directory and type ``make``.


#### Reference

##### Constructors
```cpp
// Initializes a csv data object
CSVData my_data_1(); 

// Initializes a csv data object and reads the data from <filename>
CSVData my_data_2(filename); 

// Copy-constructor
CSVData my_data_3(my_data_2);
```

##### Methods
```cpp
string filename("example.csv");

CSVData my_data(filename);

// Checks if the data have been modified. Returns true or false.
my_data.is_modified();

// Checks if all rows have the same number of columns
my_data.is_unified();

// Returns the number of rows
my_data.rows();

// Returns the number of columns. Is meaningless if is not unified
my_data.columns();

// Returns the value in a specific cell
int row = 0, column = 2;
my_data.get_value(row, column);

// Modifies the value of a cell
my_data.set_value(row, column, "42");

// Deletes an entire row
my_data.delete_row(row);

// Deletes an entire column
my_data.delete_col(int col);

// Deletes a specific cell resulting to non unified data
delete_item(row, col);

// Reads CSV file data. This replaces the old data.
my_data.read_file("ecample.csv");

// Write data into new CSV file
my_data.write_data("example1.csv");

// Convert date format of an entire column
int column = 3;
string old_format = "%d/%m/%Y", new_format = "%Y-%m-%d";
my_data.convert_date_format(old_format, new_format, column);

// Convert date format of a cell
int row = 0, column = 3;
string old_format = "%d/%m/%Y", new_format = "%Y-%m-%d";
my_data.convert_date_format(old_format, new_format, row, column);
```

#### Examples

##### Example 1

In this example we read ``date_example.csv`` file and convert the date format from ``dd/mm/YYYY`` to ``YYYY-mm-dd``.

*Usage*

```bash
csv_date_format -i <filename.csv> -f <field to be modified>
```

So with the command

```bash
csv_date_format -i test.csv -f 3
```

we get a ``<date_example_new.csf>`` file with the new date format.

#### License
See the [License](https://github.com/ApollonGT/csv_manip/blob/master/LICENSE) page.
