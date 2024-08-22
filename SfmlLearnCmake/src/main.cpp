#include <SFML/Graphics.hpp>

sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));

void move(float x, float y) {
	sf::Vector2f pos = rectangle.getOrigin();
	pos.x -= x;
	pos.y += y;
	rectangle.setOrigin(pos);
}

void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(640, 480),
		"Rendering the rectangle.");
	// Creating our shape.
	
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(320, 240);
	rectangle.setOrigin(rectangle.getSize().x / 2,
		rectangle.getSize().y / 2);
	while (window.isOpen()) {
		sf::Event event;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// left key is pressed: move our character
			move(-0.5f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// right key is pressed: move our character
			move(0.5f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// left key is pressed: move our character
			move(0.0f, 0.5f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// right key is pressed: move our character
			move(0.0f, -0.5f);
		}
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// Close window button clicked.
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		window.draw(rectangle); // Drawing our shape.
		window.display();
	}
}