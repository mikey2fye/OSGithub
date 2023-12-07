# list/Makefile
#
# Makefile for list implementation and test file.
#
# <Author: Michael J. Johnson Jr.>

CC=gcc
CFLAGS=-I
DEPS = list.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

list: list.o main.o
	$(CC) -o list list.o main.o
