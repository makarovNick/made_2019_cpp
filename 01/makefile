CC=g++

all : run

run : main.o parser.o
	$(CC) main.o parser.o -o Calculator	

test : test.o parser.o
	$(CC) test.o parser.o -o test

parser.o : parser.cpp
	$(CC) -c parser.cpp

main.o : main.cpp main.h
	$(CC) -c main.cpp

test.o : test.cpp catch.hpp main.h
	$(CC) -c test.cpp 

clean:
	rm -f *.o Calculator test 

