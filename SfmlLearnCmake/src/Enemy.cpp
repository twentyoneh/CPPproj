#include "Enemy.h"

Enemy::Enemy()
    : mHealth(100)  // ��������� �������� ����� (����� �������� �� ����� ��������)
{
    // ����� ��������� �������� � ���������� � �� ������
    // ��� ����� ��� ����� �������� ���� � �������� ��� ������������ ��������� ��������
    // ��������, ���:
    // sf::Texture texture;
    // if (texture.loadFromFile("enemy_texture.png")) {
    //     mSprite.setTexture(texture);
    // }

    // ������������� ������� �����-������ ��������� �������
    mSprite.setPosition(100.f, 100.f); // ��� ����� �������� ��� ������ ����������
}

Enemy::~Enemy() {
    // ����� �������� ��� ��� �������, ���� �����
}

void Enemy::update(sf::Time deltaTime) {
    // ����� ����� ���� ������ ���������� �����
    // ��������, ��������, ��������, ����� � �.�.

    // � ���������� ������ ����� ���� �������� �������� ����
    sf::Vector2f movement(0.f, 50.f * deltaTime.asSeconds());
    mSprite.move(movement);
}

void Enemy::setPosition(const sf::Vector2f& position) {
    mSprite.setPosition(position);
}

void Enemy::takeDamage(int damage) {
    mHealth -= damage;
    if (mHealth < 0) {
        mHealth = 0;  // ��������, ��� �������� �� ������ � �����
    }
}

bool Enemy::isDead() const {
    return mHealth <= 0;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states); // ��������� ������� �����
}
