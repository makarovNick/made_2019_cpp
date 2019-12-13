CC = g++
FLAGS = -pthread

all : run

run : main.o threadpool.h
	$(CC) $(FLAGS) -o example main.o

test : test.o catch.hpp threadpool.h
	$(CC) $(FLAGS) -o test test.cpp

main.o : main.cpp
	$(CC) -c main.cpp

test.o : test.cpp 
	$(CC) -c test.cpp

clean : 
	rm -f *.o example test
