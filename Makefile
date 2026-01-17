CC      = gcc
CC_FLAGS = -Wall -std=c99 -pedantic -Iinclude -Iraylib/src/
LIBS    = -lraylib

all: raylib_game

clean:
	rm -rf *.o
	rm -rf raylib_game

raylib_game: main.o rlext.o church.o sky.o sun.o gamepad.o
	$(CC) $(CC_FLAGS) $^ $(LIBS) -o $@

main.o: src/main.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

rlext.o: src/rlext.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

church.o: src/church.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

sky.o: src/sky.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

sun.o: src/sun.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

gamepad.o: src/gamepad.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

run:
	.\raylib_game
