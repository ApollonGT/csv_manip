#include <string>
#include "cli_help.hpp"

std::string get_help_text()
{
    std::string help_text("\nHelp for CSV Data Manipulator command line interface.\n\n");

    help_text.append("command list:\n");

    help_text.append("h or help\t\t:\tShow this message.\n");
    help_text.append("version\t\t\t:\tShow the current version of CSV Data Manipulator.\n");
    help_text.append("read <filename>.csv\t:\tRead the contents of <filename>.csv.\n");

    help_text.append("show rows\t\t:\tShow the total number of rows.\n");
    help_text.append("show row <n>\t\t:\tShow the contents of row <n>.\n");

    help_text.append("delete row <n>\t\t:\tDelete the row  number <n>.\n");

    help_text.append("\n");

    return help_text;
}
