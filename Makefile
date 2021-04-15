CC = gcc
CFLAGS = -g -Wall -no-pie

all: main.o main
	$(CC) $(CFLAGS) -o main main.o blackbox.o

main.o:
	$(CC) $(CFLAGS) -c -o main.o main.c

main:
	$(CC) $(CFLAGS) -o main main.o blackbox.o

clean:
	rm *.o