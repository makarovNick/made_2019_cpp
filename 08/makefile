CC = g++

all : run

run : main.o
	$(CC) -o example main.o

test : test.o
	$(CC) -o test test.o

test.o : test.cpp catch.hpp Iterator.h vector.h
	$(CC) -c test.cpp

main.o : main.cpp Iterator.h vector.h
	$(CC) -c main.cpp

clean : 
	rm -f *.o test example