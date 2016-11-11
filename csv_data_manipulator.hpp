#ifndef CSV_DATA_MANIPULATOR
#define CSV_DATA_MANIPULATOR

#include <vector>
#include <functional>

class CSVData {
    public:
        CSVData();
        CSVData(CSVData &rhs);
        CSVData(std::string filename);
        ~CSVData() {  }

        bool is_modified() { return m_is_modified; }
        bool is_unified() { return m_is_unified; }
        int  columns() { return m_cols; }
        int  rows() { return m_rows; }

        const std::string get_value(int row, int col);
        void set_value(int row, int col, std::string value);

        void delete_row(int row);
        void delete_col(int col);
        void delete_item(int row, int col);
        void delete_row_if(std::function<bool(int, int, const std::string&)> cbFun);

        void read_file(std::string filename);
        void write_data(std::string filename);

        void convert_date_format(std::string old_format, std::string new_format, int column);
        void convert_date_format(std::string old_format, std::string new_format, int row, int column);

    private:
        std::vector< std::vector<std::string> > m_data;

        bool m_is_modified;
        bool m_is_unified;
        int m_rows;
        int m_cols;

        static const char CSV_DELIMITER = ',';

}; // CSVData

#endif /* CSV_DATA_MANIPULATOR */
