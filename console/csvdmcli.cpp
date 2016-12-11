#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "curses.h"
#include "string.h"

#include "../csv_data_manipulator.hpp"

using namespace std;

enum {
    CSV_CMD_READ = 1,

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

    return true;
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
        output.assign("Valid command ");
        output.append(std::to_string(cmd_code->second));
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
