#include "Player.h"

Player::Player()
    : mSpeed(200.f) // ������������� �������� ������
    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)
{
    loadTexture();
    mSprite.setTexture(mTexture);
    mSprite.setPosition(400.f, 300.f); // ��������� ������� ������
}

Player::~Player() {
    // ������������ ��������, ���� ����������
}

void Player::loadTexture() {
    if (!mTexture.loadFromFile("assets/images/player.png")) {
        // ��������� ������ �������� ��������
        throw std::runtime_error("Failed to load player texture");
    }
}

void Player::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (mIsMovingUp) {
        movement.y -= mSpeed;
    }
    if (mIsMovingDown) {
        movement.y += mSpeed;
    }
    if (mIsMovingLeft) {
        movement.x -= mSpeed;
    }
    if (mIsMovingRight) {
        movement.x += mSpeed;
    }

    mSprite.move(movement * deltaTime.asSeconds()); // ����������� ������
}

void Player::moveUp(bool isMoving) {
    mIsMovingUp = isMoving;
}

void Player::moveDown(bool isMoving) {
    mIsMovingDown = isMoving;
}

void Player::moveLeft(bool isMoving) {
    mIsMovingLeft = isMoving;
}

void Player::moveRight(bool isMoving) {
    mIsMovingRight = isMoving;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}