#include "Enemy.h"

Enemy::Enemy()
    : mHealth(100)  // Ќачальное здоровье врага (можно помен€ть на любое значение)
{
    // ћожно загрузить текстуру и установить еЄ на спрайт
    // ƒл€ этого вам нужно передать путь к текстуре или использовать ресурсный менеджер
    // Ќапример, так:
    // sf::Texture texture;
    // if (texture.loadFromFile("enemy_texture.png")) {
    //     mSprite.setTexture(texture);
    // }

    // ”станавливаем спрайту какую-нибудь начальную позицию
    mSprite.setPosition(100.f, 100.f); // Ёто можно изменить под нужные координаты
}

Enemy::~Enemy() {
    // ћожно добавить код дл€ очистки, если нужно
}

void Enemy::update(sf::Time deltaTime) {
    // «десь может быть логика обновлени€ врага
    // Ќапример, движение, анимаци€, атака и т.д.

    // ¬ простейшем случае пусть враг медленно движетс€ вниз
    sf::Vector2f movement(0.f, 50.f * deltaTime.asSeconds());
    mSprite.move(movement);
}

void Enemy::setPosition(const sf::Vector2f& position) {
    mSprite.setPosition(position);
}

void Enemy::takeDamage(int damage) {
    mHealth -= damage;
    if (mHealth < 0) {
        mHealth = 0;  // ”бедимс€, что здоровье не уходит в минус
    }
}

bool Enemy::isDead() const {
    return mHealth <= 0;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states); // ќтрисовка спрайта врага
}
