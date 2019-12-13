CC = g++
FLAGS = -pthread

all : run

run : main.o limited_sorter.o
	$(CC) $(FLAGS) -o sort main.o limited_sorter.o

naive : naive_sorter.cpp
	$(CC) -o naive_sort naive_sorter.cpp

main.o : main.cpp
	$(CC) -c main.cpp

generate : generate_uint.cpp
	$(CC) -o generate_uint64 generate_uint.cpp

Sorter.o : limited_sorter.cpp
	$(CC) -c limited_sorter.cpp 

clean : 
	rm -f *.o generate_uint64 input sort output* _temp_* read_binary *.out

read : read_binary.cpp
	$(CC) -o read_binary read_binary.cpp