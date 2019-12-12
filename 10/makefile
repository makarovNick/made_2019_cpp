CC = g++
FLAGS = -pthread

all : run

run : main.o
	$(CC) $(FLAGS) main.o

generate : randints.cpp
	$(CC) -o generate_uint64 randints.cpp

clean : 
	rm -f *.out generate_uint64 input