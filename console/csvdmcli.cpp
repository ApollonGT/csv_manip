#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "curses.h"
#include "string.h"

#include "../csv_data_manipulator.hpp"
#include "cli_help.hpp"

using namespace std;

enum {
    CSV_CMD_READ = 1,
    CSV_CMD_SHOW,
    CSV_CMD_VERSION,
    CSV_CMD_DELETE,
    CSV_CMD_HELP,

    CSV_CMD_END
};

void remove_multiple_spaces(std::string &str_command)
{
    std::string search_1("  ");
    std::string search_2("\t");
    size_t idx;

    while ( (idx = str_command.find(search_2)) != std::string::npos ) {
        str_command.replace(idx, 1, " ");
    }

    while ( (idx = str_command.find(search_1)) != std::string::npos ) {
        str_command.erase(idx, 1);
    }
}

bool add_item_to_map(std::map<std::string, int> &command_map, std::string key, int value)
{
    std::pair<std::map<std::string, int>::iterator, bool> ret;
    ret = command_map.insert(std::pair<std::string, int>(key, value));
    return ret.second;
}


bool init_command_map(std::map<std::string, int> &command_map)
{
    if (!add_item_to_map(command_map, "read", CSV_CMD_READ)) return false;
    if (!add_item_to_map(command_map, "show", CSV_CMD_SHOW)) return false;
    if (!add_item_to_map(command_map, "version", CSV_CMD_VERSION)) return false;
    if (!add_item_to_map(command_map, "delete", CSV_CMD_DELETE)) return false;
    if (!add_item_to_map(command_map, "h", CSV_CMD_HELP)) return false;
    if (!add_item_to_map(command_map, "help", CSV_CMD_HELP)) return false;

    return true;
}

std::string execute_known_command(CSVData &main_data, int cmd_code, std::vector<std::string> command_list)
{
    std::string ret_val;
    switch (cmd_code) {
        case CSV_CMD_READ:
            if (command_list.size() > 1) {
                std::ifstream file(command_list[1]);
                if (file.good()) {
                    main_data.read_file(command_list[1]);
                    ret_val.assign("Reading from: '");
                    ret_val.append(command_list[1]);
                    ret_val.append("' completed!");
                } else {
                    ret_val.assign("Cannot access file.");
                }
            } else {
                ret_val.assign("No filename specified.");
            }
            break;
        case CSV_CMD_SHOW:
            if (command_list.size() > 1) {
                ret_val.clear();
                std::vector<std::string>::iterator it;
                if ( (it = std::find(command_list.begin(), command_list.end(), "rows")) != command_list.end()) {
                    ret_val.append("Rows: ");
                    ret_val.append(std::to_string(main_data.rows()));
                } else if ( (it = std::find(command_list.begin(), command_list.end(), "columns")) != command_list.end()) {
                    ret_val.append("Columns: ");
                    ret_val.append(std::to_string(main_data.columns()));
                } else if ( (it = std::find(command_list.begin(), command_list.end(), "row")) != command_list.end()) {
                    *it++;
                    std::string row_idx = *it;
                    int i_row_idx;
                    bool error = false;

                    try {
                        i_row_idx = std::stol(row_idx);
                    } catch (const invalid_argument& ia) {
                        error = true;
                    }

                    if (error) {
                         ret_val.append("Invalid row index.");
                    } else if (i_row_idx < 1 || i_row_idx > main_data.rows()) {
                         ret_val.append("Index out of range.");
                    } else {
                        ret_val.append("Row "+to_string(i_row_idx)+" : ");
                        std::vector<std::string> row_data = main_data.get_row(i_row_idx - 1);
                        for (int i = 0; i < row_data.size(); i++) ret_val.append(row_data.at(i)+",");
                    }
                } else {
                    ret_val.assign("Invalid parameter.");
                }
            } else {
                ret_val.assign("Missing parameter...");
            }
            break;
        case CSV_CMD_DELETE:
            if (command_list.size() > 1) {
                ret_val.clear();
                std::vector<std::string>::iterator it;
                if ( (it = std::find(command_list.begin(), command_list.end(), "row")) != command_list.end()) {
                    *it++;
                    std::string row_idx = *it;
                    int i_row_idx;
                    bool error = false;

                    try {
                        i_row_idx = std::stol(row_idx);
                    } catch (const invalid_argument& ia) {
                        error = true;
                    }

                    if (error) {
                         ret_val.append("Invalid row index.");
                    } else if (i_row_idx < 1 || i_row_idx > main_data.rows()) {
                         ret_val.append("Index out of range.");
                    } else {
                        main_data.delete_row(i_row_idx - 1);
                        ret_val.append("Row "+row_idx+" deleted.");
                    }
                } else {
                    ret_val.assign("Invalid parameter.");
                }
            } else {
                ret_val.assign("Missing parameter...");
            }
            break;
        case CSV_CMD_VERSION:
            ret_val.assign(main_data.get_version());
            break;
        case CSV_CMD_HELP:
            ret_val.assign(get_help_text());
            break;
        default:
            ret_val.assign("Invalid command.");
            break;
    }
    return ret_val;
}

bool run_command(CSVData &main_data, std::map<std::string, int> &command_map, std::string command, std::string &output)
{
    output.clear();

    if (command.size() == 0) return true;

    std::vector<std::string> command_list;
    std::string command_part;

    std::stringstream total_command(command);

    while (std::getline(total_command, command_part, ' ')) {
         command_list.push_back(command_part);
    }

    std::map<std::string, int>::iterator cmd_code = command_map.find(command_list.at(0));

    if (cmd_code == command_map.end()) {
        output.assign("Invalid command '");
        output.append(command_list.at(0));
        output.append("'.");
    } else {
        std::string exe_out = execute_known_command(main_data, cmd_code->second, command_list);
        output.assign(exe_out);
    }

    return true;
}

void init_screen(CSVData &main_data)
{
    clear();
    printw(" ***********************************\n");
    printw(" *** CSV Data Manipulator %s  ***\n", main_data.get_version());
    printw(" *** type h for help             ***\n");
    printw(" *** type q to quit              ***\n");
    printw(" ***********************************\n\n");
}

int main(int argc, char *argv[])
{
    char        command[1024] = {'\0'};

    std::string output;
    CSVData     main_data;

    std::map<std::string, int> command_map;

    if (!init_command_map(command_map)) {
        std::cout << "Error: duplicated entry in command map initialization..." << std::endl;
        return EXIT_FAILURE;
    }

    initscr();
    init_screen(main_data);

    while (strcmp(command, "q") && strcmp(command, "quit")) {
        addstr(" csv command> ");
        refresh();
        getnstr(command, sizeof(command) - 1);

        std::string str_command(command);

        remove_multiple_spaces(str_command);

        if (!run_command(main_data, command_map, str_command, output)) {
             std::cout << "Error: could not execute command..." << std::endl;
             return EXIT_FAILURE;
        }

        init_screen(main_data);
        printw(" Response:  %s\n", output.c_str());
        refresh();
    }

    endwin();

    return EXIT_SUCCESS;
}
