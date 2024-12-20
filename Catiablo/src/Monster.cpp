#include "../inc/Monster.h"
#include <cmath>

Monster::Monster(const std::string& texturePath, sf::Vector2f position) {
    if (!m_texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Не удалось загрузить текстуру монстра");
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(position);
    m_sprite.setScale(0.1f, 0.1f);
}

void Monster::update(float deltaTime, sf::Vector2f playerPosition) {
    sf::Vector2f direction = playerPosition - m_sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) direction /= length; // Нормализация
    m_sprite.move(direction * m_speed * deltaTime);
}

void Monster::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}
