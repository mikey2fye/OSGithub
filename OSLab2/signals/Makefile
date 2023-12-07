CC=gcc
CFLAGS=-I.

all: signal timer

signal: signal.o
	$(CC) -o signal signal.o

signal.o: signal.c
	$(CC) -c signal.c
	
timer: timer.o
	$(CC) -o timer timer.o

timer.o: timer.c
	$(CC) -c timer.c