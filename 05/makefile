CC = g++

all : run

run : main.o Deserializer.o Serializer.o
	$(CC) -o example main.o Deserializer.o Serializer.o

main.o : main.cpp Deserializer.h Serializer.h
	$(CC) -c main.cpp 

Deserializer.o : Deserializer.cpp Deserializer.h
	$(CC) -c Deserializer.cpp

Serializer.o : Serializer.cpp Serializer.h
	$(CC) -c Serializer.cpp

clean : 
	rm -f *.o example test
