CC = g++
FLAGS = -pthread

all : run

run : main.o ThreadPool.h
	$(CC) $(FLAGS) -o example main.o

main.o : main.cpp
	$(CC) -c main.cpp

clean : 
	rm -f *.o example test
