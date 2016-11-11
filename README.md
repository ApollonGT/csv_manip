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
my_data.delete_col(column);

// Deletes a specific cell resulting to non unified data
delete_item(row, column);

// Reads CSV file data. This replaces the old data.
my_data.read_file("ecample.csv");

// Write data into new CSV file
my_data.write_data("example1.csv");

// Convert date format of an entire column
int column = 3;
string old_format("%d/%m/%Y")
string new_format("%Y-%m-%d");
my_data.convert_date_format(old_format, new_format, column);

// Convert date format of a cell
int row = 0;
int column = 3;
string old_format("%d/%m/%Y")
string new_format("%Y-%m-%d");
my_data.convert_date_format(old_format, new_format, row, column);
```

##### Delete If

An extra method has been added, but because of it's importance I will mention it separately. This API will be used as a tool for csv data manipulation.
The first step in these cases is to filter your data and remove the useless entries (extreme values etc.). The ``delete_row_if`` method is exactly for this purpose.

*Usage*

```cpp
bool id_is_even(int row, int col, const string &val)
{
    int i_val = atoi( val.c_str() );
    if ( col == 0 && i_val > 0 && i_val % 2 == 0 ) return true;
    return false;
}

CSVData my_data("test_data.csv");

// This will delete all rows where the first column is even number, greater than zero.
my_data.delete_row_if(id_is_even);
```

#### Remarks

* Note that all indices are zero-based. Which means the first row is ``int row = 0;`` and the first column is ``int col = 0;``.
* Note that the callback of ``delete_row_if`` method must be of the form:

    ```cpp
    bool <function_name>(int row, int col, const string &value);
    ```

    When the callback returns ``true`` the row will be deleted.

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
