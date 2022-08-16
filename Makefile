SRC = collision.cpp
EXEC = collision
CC = g++

all: $(SRC)
	$(CC) $(SRC) `sdl2-config --cflags --libs` -o $(EXEC)

clean:
	rm $(EXEC)
