TARGET="csvdmcli"
CPP=g++
CC=gcc
CPPFLAGS= -std=c++11
LINK= -lncurses

debug: csvdmcli.o csv_data_manipulator.o
	@echo "Linking $(TARGET)"
	@$(CPP) -o $(TARGET) csvdmcli.o csv_data_manipulator.o $(LINK)

csvdmcli.o : csvdmcli.cpp ../csv_data_manipulator.hpp
	@echo "Compiling $(TARGET)"
	@$(CPP) -c csvdmcli.cpp $(CPPFLAGS) $(LINK)

csv_data_manipulator.o : ../csv_data_manipulator.cpp ../csv_data_manipulator.hpp
	@echo "Compiling csv_data_manipulator"
	@$(CPP) -c ../csv_data_manipulator.cpp $(CPPFLAGS)

clean:
	@echo "Cleaning up"
	@rm -f $(TARGET) csvdmcli.o csv_data_manipulator.o
