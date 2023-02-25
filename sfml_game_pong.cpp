#include <SFML/Graphics.hpp>

float const width = 900;
float const height = 650;

int check_collision(sf::Vector2f player, sf::Vector2f ball) {
	if (ball.x + 40 > player.x && ball.x < player.x + 100 && ball.y + 40 >= player.y)
		return 1;
	return 0;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(width,height), "Game");
	window.setFramerateLimit(60);

	// Player
	float vp = 5;

	sf::RectangleShape player;
	sf::Vector2f pos1 = sf::Vector2f(width/2 - 50, height - 40);
	player.setPosition(pos1);
	player.setSize(sf::Vector2f(100,20));

	// Ball
	float vx = 3;
	float vy = 3;

	sf::RectangleShape ball;
	sf::Vector2f pos2 = sf::Vector2f(300,200);
	ball.setPosition(pos2);
	ball.setSize(sf::Vector2f(40,40));


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) pos1.x -= vp;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pos1.x += vp;
		}
		player.setPosition(pos1);

		pos2.x += vx;
		pos2.y += vy;

		if (pos2.x <= 0 || pos2.x+40 >= width) vx *= -1;
		if (pos2.y <= 0 || check_collision(pos1, pos2)) vy *= -1;
		if (pos2.y >= height) window.close();
		
		ball.setPosition(pos2);

		window.clear();
		window.draw(ball);
		window.draw(player);
		window.display();
	}

    return 0;
}
