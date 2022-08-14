SRC = game.c

EXEC = game

all: $(SRC)
	gcc $(SRC) `sdl2-config --cflags --libs` -o $(EXEC)
