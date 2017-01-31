TARGET="csvdmcli"
CPP=g++
CC=gcc
CPPFLAGS= -std=c++11
LINK= -lncurses

debug: csvdmcli.o csv_data_manipulator.o cli_help.o
	@echo "Linking $(TARGET)"
	@$(CPP) -o $(TARGET) csvdmcli.o csv_data_manipulator.o cli_help.o $(LINK)

csvdmcli.o : csvdmcli.cpp ../csv_data_manipulator.hpp cli_help.hpp
	@echo "Compiling $(TARGET)"
	@$(CPP) -c csvdmcli.cpp $(CPPFLAGS) $(LINK)

cli_help.o : cli_help.cpp cli_help.hpp
	@echo "Compiling cli_help"
	@$(CPP) -c cli_help.cpp $(CPPFLAGS)

csv_data_manipulator.o : ../csv_data_manipulator.cpp ../csv_data_manipulator.hpp
	@echo "Compiling csv_data_manipulator"
	@$(CPP) -c ../csv_data_manipulator.cpp $(CPPFLAGS)

clean:
	@echo "Cleaning up"
	@rm -f $(TARGET) csvdmcli.o csv_data_manipulator.o cli_help.o
