CC = gcc
CFLAGS = -g -Wall #-no-pie

all: main.o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

main: main.o blackbox.c
	$(CC) $(CFLAGS) -o main main.o blackbox.o

clean:
	rm *.o