CPP=g++
CC=gcc
CPPFLAGS= -std=c++11

debug: csv_date_format.cpp
	$(CPP) csv_date_format.cpp -o csv_date_format $(CPPFLAGS)

clean:
	rm -f csv_date_format.o csv_date_format
