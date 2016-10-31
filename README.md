### CSV Date format

A simple C++ program that converts the date format of a ``.csv`` file from ``dd/mm/YYYY`` to ``YYYY-mm-dd``.

A possible application could be to prepare a ``.csv`` to be imported in a SQLite database.

#### Usage
```bash
csv_date_format -i <filename.csv> -f <field to be modified>
```

#### Example
```bash
csv_date_format -i test.csv -f 3
```

#### Result
This will create a ``<filename_new.csf>`` file with the new date format.
