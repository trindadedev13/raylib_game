CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
LIBS = -lraylib

all:
	$(CC) main.c -o main $(CFLAGS) $(LIBS)

run:
	./main
