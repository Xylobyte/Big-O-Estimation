CC = gcc
CFLAGS = -g -Wall -no-pie

all: main

main: main.c blackbox.o
	$(CC) $(CFLAGS) -o main main.c blackbox.o

clean:
	rm *.o