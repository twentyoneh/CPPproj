#pragma once
#include"Bullet.h"
#include"ResourceManager.h"

class Fireball : public Bullet
{
public:
	Fireball(sf::Vector2f pos, sf::Vector2f origin);
	~Fireball();

	sf::Vector2f getPosition(void) override;
	sf::Vector2f getOrigin(void) override;
private:
	sf::Vector2f m_position;
	sf::Vector2f m_origin;
	sf::Sprite mSprite;

	void draw(sf::RenderTarget& target);
	void update(float dt); // Optional for movement or animation
	
};