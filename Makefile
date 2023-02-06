NAME=game

all: $(SRC)
	g++ -c $(NAME).cpp
	g++ $(NAME).o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm $(NAME).o
	rm sfml-app
