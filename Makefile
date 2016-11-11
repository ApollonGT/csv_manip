TARGET="cvs_examples"
CPP=g++
CC=gcc
CPPFLAGS= -std=c++11

debug: examples.o csv_data_manipulator.o
	@echo "Linking $(TARGET)"
	@$(CPP) -o $(TARGET) examples.o csv_data_manipulator.o

examples.o : examples.cpp csv_data_manipulator.hpp
	@echo "Compiling examples"
	@$(CPP) -c examples.cpp $(CPPFLAGS)

csv_data_manipulator.o : csv_data_manipulator.cpp csv_data_manipulator.hpp
	@echo "Compiling csv_data_manipulator"
	@$(CPP) -c csv_data_manipulator.cpp $(CPPFLAGS)

clean:
	@echo "Cleaning up"
	@rm -f $(TARGET) examples.o csv_data_manipulator.o
