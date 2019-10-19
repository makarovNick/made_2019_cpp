CC = g++

all : run

run : main.o allocator.o allocator.h
	$(CC) -o malloc_compare main.o allocator.o

test : test.o allocator.o allocator.h catch.hpp
	$(CC) -o test test.o allocator.o

allocator.o : allocator.cpp
	$(CC) -c allocator.cpp

main.o : main.cpp
	$(CC) -c main.cpp

test.o : test.cpp 
	$(CC) -c test.cpp

clean :
	rm *.o malloc_compare 
