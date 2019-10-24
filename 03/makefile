CC = g++

all : run

run : libparser.a main.o
	$(CC) -o example main.o -L. -lparser

main.o : main.cpp parser.h
	$(CC) -c main.cpp

libparser.a : parser.o
	ar rcs libparser.a parser.o

parser.o : parser.cpp parser.h
	$(CC) -c parser.cpp

test : libparser.a test.o
	$(CC) -o test test.o -L. -lparser

test.o : test.cpp catch.hpp parser.h
	$(CC) -c test.cpp

clean : 
	rm -f *.o *.a example test
