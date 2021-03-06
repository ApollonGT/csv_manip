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

// Adds new row in the end of the file
vector<string> new_row;
[... add values in new_row ...]
my_data.add_row(new_row);

// Adds new row in the defined position. pos = 0 is the first row.
int pos = 0;
my_data.add_row(new_row, pos);

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

// Sort rows by column values
my_data.sort_by_col(column, CSVData::ACS);

// Append some data from a file to existing data
my_data.append_file("new_file.csv");

// Make data unique
my_data.make_data_unique();
// Note: This method works only on unified data, 
//       which means all the rows must have the same number of columns.
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
* To clean up the object files and the executables, type ``make clean``.
* Note that the sorting method checks for numbers otherwise sorts alphanumerically. A date is considered as string.
* sort_by_col second argument can be *CSVData::ACS* or *CSVData::DECS*
* Note that delete_row_if can be called in three ways:
    ```cpp
    bool function_1(int row, int col, const std::string &value) 
    {
        // This function runs on each cell of the data.
        // The 'value' is the value of the cell.
    }

    bool function_2(int row, int col, const std::string &value, void *cbData)
    {
        // This function runs on each cell of the data.
        // The 'value' is the value of the cell.
        // The 'cbData' is the callback data that can be passed by the user.

        // To access data:
        std::string data = *(std::string *)cbData;
    }

    bool function_3(int row, const std::vector< std::string > &row_data, void *cbData)
    {
        // This function runs on each row of the data.
        // The 'row_data' is a vector that contains the values of the specific row.
        // The 'cbData' is the callback data that can be passed by the user.

        // To access data:
        std::string data = *(std::string *)cbData;
    }

    std::string cbData("remove_me");

    my_data.delete_row_if(function_1);
    my_data.delete_row_if(function_2, &cbData);
    my_data.delete_row_if(function_3, &cbData);
    ```

#### Examples

To compile each example, use ``make example#``. If you want to compile example 1 type ``make example1``. 
The executables and the csv files are located in the ``examples`` folder.

##### Example 1

In this example we read ``example_1_data.csv`` file and convert the date format from ``dd/mm/YYYY`` to ``YYYY-mm-dd``.

*Usage*

```bash
cd examples
./example_1 -i <filename>.csv -f <field to be modified>
```

So with the command

```bash
./example_1 -i example_1_data.csv -f 3
```

we get a ``example_1_data_new.csv`` file with the new date format.

##### Example 2

Lets assume we have entries where the first column is the id of the entry and we want to keep only the entries with odd ids.
In this example we read ``example_2_data.csv`` file and remove all the rows that have even number in the first column.

*Usage*

```bash
cd examples
./example_2 -i <filename>.csv
```

So with the command

```bash
./example_2 -i example_2_data.csv
```

we get a ``example_2_data_new.csv`` file which contains only the data of the ``example_2_data.csv`` that have odd number in the first column.

##### Example 3

Lets assume we have entries where the first column is the id of the entry but the rows are shuffled. We need to sort the data by id.
In this example we read ``example_3_data.csv`` file and sort the data by the first column.

*Usage*

```bash
cd examples
./example_3 -i <filename>.csv -c <column>
```

So with the command

```bash
./example_3 -i example_3_data.csv -c 0
```

we get a ``example_3_data_new.csv`` file which contains the data of the ``example_3_data.csv`` sorted by the first column.

##### Example 4

Lets assume we have multiple files and we want to merge the data and manipulate them as one set of data.
In this example we read ``example_4_data_1.csv`` file and then ``example_4_data_2.csv`` in the same data. Then we output the results in a final file.

*Usage*

```bash
cd examples
./example_4 -i <filename>.csv -a <filename>.csv
```

So with the command

```bash
./example_4 -i example_4_data_1.csv -a example_4_data_2.csv
```

we get a ``example_4_data_new.csv`` file which contains the data of the ``example_4_data_1.csv`` and ``example_4_data_2.csv`` merged in one file.

##### Example 5

In this example we test the experimental functionality of making the data unique using the ``make_data_unique`` method.
In the example 5 the filenames are hardcoded inside the source file ``example_5.cpp``. Just compile it and run it.

*Usage*

```bash
cd examples
./example_5
```

So the command

```bash
./example_5
```

outputs a ``example_5_data_new.csv`` file which contains the data of the ``example_5_data.csv`` without repeating rows.

#### License
See the [License](https://github.com/ApollonGT/csv_manip/blob/master/LICENSE) page.
