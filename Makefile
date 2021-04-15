CC = gcc
CFLAGS = -g -Wall -no-pie

all: main.o main

main.o:
	$(CC) $(CFLAGS) -c main.c

main:
	$(CC) $(CFLAGS) -o main main.o blackbox.o

clean:
	rm *.o