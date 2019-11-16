CC = g++

all : run

run : main.o BigInt.o
	$(CC) -o example main.o BigInt.o

test : test.o BigInt.o
	$(CC) -o test test.o BigInt.o

main.o : main.cpp BigInt.h
	$(CC) -c main.cpp

test.o : test.cpp catch.hpp BigInt.h
	$(CC) -c test.cpp 

BigInt.o : BigInt.cpp BigInt.h
	$(CC) -c BigInt.cpp

clean : 
	rm -f *.o test example
