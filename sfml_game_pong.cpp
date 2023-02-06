#include <SFML/Graphics.hpp>

int const width = 900;
int const height = 650;

class player {
	public:
		player(width, height);

		float vx = 5;
		float vy = 5;
};

player::player(int width, int height) {
	sf::RectangleShape rect;
	sf::Vector2f pos(width/2 - 50, height/2 + 40);
	rect.setPosition(pos);
	rect.setSize(sf::Vector2f(100,20));
}

void player::move(sf::Event event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) pos.x -= vx;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pos.x += vx;
	rect.setPosition(pos);
}

void player::show(sf::RenderWindow window) {
	window.clear();
	window.draw(rect);
	window.display();
}


int main() {
	sf::RenderWindow window(sf::VideoMode(width,height), "Game");
	window.setFramerateLimit(60);

	player player;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			player.move(event);
		}
		/* if (pos.x <= 0 || pos.x+100 >= width) vx *= -1; */
		/* if (pos.y <= 0 || pos.y+100 >= height) vy *= -1; */

		player.show();
	}

    return 0;
}
