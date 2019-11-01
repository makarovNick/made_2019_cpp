CC = g++

all : run

run : main.o Matrix.o
	$(CC) -o example main.o Matrix.o

main.o : main.cpp Matrix.h
	$(CC) -c main.cpp

Matrix.o : Matrix.cpp Matrix.h
	$(CC) -c Matrix.cpp

test : test.o Matrix.o
	$(CC) -o test test.o Matrix.o

test.o : test.cpp Matrix.h catch.hpp
	$(CC) -c test.cpp

clean : 
	rm -f *.o example test 
