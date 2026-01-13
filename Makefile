CC = gcc
CFLAGS = -Wall -std=c90
LIBS = -lraylib

all:
	$(CC) main.c -o main $(CFLAGS) $(LIBS)

build:
	 gcc main.c -o jogo

run:
	./main 

buildR:
	make
	make run	
