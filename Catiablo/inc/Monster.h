#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>

class Monster {
public:
    Monster(const std::string& texturePath, sf::Vector2f position);
    void update(float deltaTime, sf::Vector2f playerPosition);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    float m_speed = 100.f; // Скорость врага
};

#endif // MONSTER_H
