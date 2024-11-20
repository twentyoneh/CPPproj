#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	virtual sf::Vector2f getPosition(void) = 0;
	virtual sf::Vector2f getOrigin(void) = 0;
};
