CC=g++

all : run

run : main.o
	$(CC) main.o -o Calculator	

tests : tests.o main.h
	$(CC) tests.o -o tests

main.o : main.cpp main.h
	$(CC) -c main.cpp

tests.o : tests.cpp catch.hpp main.h
	$(CC) -c tests.cpp

clean:
	rm -f *.o Calculator tests 

