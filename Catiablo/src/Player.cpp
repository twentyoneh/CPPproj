#include "../inc/Player.h"

Player::Player(const std::string& texturePath) {
    if (!m_texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Не удалось загрузить текстуру игрока");
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(400, 300); // Начальная позиция
    m_sprite.setScale(0.15f, 0.15f);
}

void Player::handleInput() {
    m_velocity = {0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_velocity.y -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_velocity.y += m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_velocity.x -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_velocity.x += m_speed;
}

void Player::update(float deltaTime) {
    m_sprite.move(m_velocity * deltaTime);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const {
    return m_sprite.getPosition();
}
