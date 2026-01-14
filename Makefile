CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
LIBS = -lraylib

all:
	$(CC) main.c -o raylib_game $(CFLAGS) $(LIBS)

run:
	./raylib_game
