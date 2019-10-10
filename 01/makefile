CC=g++

all : run

run : main.o
	$(CC) main.o -o Calculator	

test : test.o main.h
	$(CC) test.o -o test

main.o : main.cpp main.h
	$(CC) -c main.cpp

test.o : test.cpp catch.hpp main.h
	$(CC) -c test.cpp

clean:
	rm -f *.o Calculator tests 

