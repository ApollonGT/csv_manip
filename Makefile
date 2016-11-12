TARGET="csv_experiments"
CPP=g++
CC=gcc
CPPFLAGS= -std=c++11

debug: experiments.o csv_data_manipulator.o
	@echo "Linking $(TARGET)"
	@$(CPP) -o $(TARGET) experiments.o csv_data_manipulator.o

experiments.o : experiments.cpp csv_data_manipulator.hpp
	@echo "Compiling experiments"
	@$(CPP) -c experiments.cpp $(CPPFLAGS)

csv_data_manipulator.o : csv_data_manipulator.cpp csv_data_manipulator.hpp
	@echo "Compiling csv_data_manipulator"
	@$(CPP) -c csv_data_manipulator.cpp $(CPPFLAGS)

EXAMPLE1="examples/example_1"

example1: example1.o csv_data_manipulator.o
	@echo "Linking $(EXAMPLE1)"
	@$(CPP) -o $(EXAMPLE1) examples/example_1.o csv_data_manipulator.o

example1.o : examples/example_1.cpp csv_data_manipulator.hpp
	@echo "Compiling example 1"
	@$(CPP) -c examples/example_1.cpp -o examples/example_1.o $(CPPFLAGS)

EXAMPLE2="examples/example_2"

example2: example2.o csv_data_manipulator.o
	@echo "Linking $(EXAMPLE2)"
	@$(CPP) -o $(EXAMPLE2) examples/example_2.o csv_data_manipulator.o

example2.o : examples/example_2.cpp csv_data_manipulator.hpp
	@echo "Compiling example 2"
	@$(CPP) -c examples/example_2.cpp -o examples/example_2.o $(CPPFLAGS)

clean:
	@echo "Cleaning up"
	@rm -f $(TARGET) experiments.o csv_data_manipulator.o
	@rm -f $(EXAMPLE1) examples/example_1.o
	@rm -f $(EXAMPLE2) examples/example_2.o
