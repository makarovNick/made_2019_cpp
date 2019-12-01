CC = g++

all : run

run : main.o 
	$(CC) -o example main.o

test : test.o 
	$(CC) -o test test.o

main.o : main.cpp format.h
	$(CC) -c main.cpp

test.o : test.cpp catch.hpp format.h
	$(CC) -c test.cpp

clean : 
	rm -f *.o example test