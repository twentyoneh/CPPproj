#include "Fireball.h"
#include "Fireball.h"
#include "Fireball.h"
#include "Fireball.h"
#include "Fireball.h"
#include"../include/Fireball.h"


Fireball::Fireball(sf::Vector2f pos, sf::Vector2f origin)	:
	m_position{ pos }, 
	m_origin{ origin }
{
	mSprite.setTexture(resourceManager.getTexture("fireball"));
	mSprite.setPosition(m_position);
}

Fireball::~Fireball()
{
}

sf::Vector2f Fireball::getPosition(void)
{
	return m_position;
}

sf::Vector2f Fireball::getOrigin(void)
{
	return m_origin;
}

void Fireball::draw(sf::RenderTarget& target) {
	target.draw(mSprite); // Render the sprite to the screen
}

void Fireball::update(float dt) {
	// Optional: Update position or animation
	m_position.x += 100.0f * dt; // Example of movement along X-axis
	mSprite.setPosition(m_position);
}