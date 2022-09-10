SRC = game.cpp
EXEC = game
CC = g++

all: $(SRC)
	$(CC) $(SRC) `sdl2-config --cflags --libs` -o $(EXEC)

clean:
	rm $(EXEC)
