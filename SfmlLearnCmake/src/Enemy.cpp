#include "Enemy.h"

Enemy::Enemy()
    : mSpeed(100.f), mDirection(1.f, 0.f) // ������������� �������� ����� � ��������� �����������
{
    loadTexture();
    mSprite.setTexture(mTexture);
    mSprite.setPosition(600.f, 300.f); // ��������� ������� �����
}

Enemy::~Enemy() {
    // ������������ ��������, ���� ����������
}

void Enemy::loadTexture() {
    if (!mTexture.loadFromFile("assets/images/enemy.png")) {
        throw std::runtime_error("Failed to load enemy texture");
    }
}

void Enemy::update(sf::Time deltaTime) {
    // ������� �������� ����� � ����� �����������
    sf::Vector2f movement = mDirection * mSpeed * deltaTime.asSeconds();
    mSprite.move(movement);

    // ������ ��� ��������� �����������, ���� ���� ��������� ������� ������
    if (mSprite.getPosition().x < 0.f || mSprite.getPosition().x > 800.f) {
        mDirection.x = -mDirection.x; // ������ ����������� �� ��� X
    }
    if (mSprite.getPosition().y < 0.f || mSprite.getPosition().y > 600.f) {
        mDirection.y = -mDirection.y; // ������ ����������� �� ��� Y
    }
}

void Enemy::setPosition(float x, float y) {
    mSprite.setPosition(x, y);
}

sf::Vector2f Enemy::getPosition() const {
    return mSprite.getPosition();
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}