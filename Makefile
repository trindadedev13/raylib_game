CC      = gcc
CC_FLAGS = -Wall -std=c99 -pedantic -Iinclude
LIBS    = -L"C:/raylib/lib" -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32

all: raylib_game.exe

clean:
	del /Q *.o
	del /Q raylib_game.exe

raylib_game.exe: main.o rlext.o church.o sun.o
	$(CC) $(CC_FLAGS) $^ $(LIBS) -o $@

main.o: src/main.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

rlext.o: src/rlext.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

church.o: src/church.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

sun.o: src/sun.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

run:
	.\raylib_game.exe