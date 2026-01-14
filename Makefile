CC       = gcc
CC_FLAGS = -Wall -std=c99 -pedantic
LIBS     = -lraylib

all: raylib_game

clean:
	rm -rf *.o
	rm -rf raylib_game

raylib_game: main.o
	$(CC) $(CC_FLAGS) $(LIBS) $^ -o $@

main.o: src/main.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

run:
	./raylib_game
