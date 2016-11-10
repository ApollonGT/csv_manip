CPP=g++
CC=gcc
CPPFLAGS= -std=c++11

debug: csv_date_format.o csv_data_manipulator.o
	$(CPP) -o csv_date_format csv_date_format.o csv_data_manipulator.o

csv_date_format.o : csv_date_format.cpp csv_data_manipulator.hpp
	$(CPP) -c csv_date_format.cpp $(CPPFLAGS)

csv_data_manipulator.o : csv_data_manipulator.cpp csv_data_manipulator.hpp
	$(CPP) -c csv_data_manipulator.cpp $(CPPFLAGS)

clean:
	rm -f csv_date_format csv_date_format.o csv_data_manipulator.o
