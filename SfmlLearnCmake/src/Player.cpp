#include "Player.h"

Player::Player()
{
}

Player::Player(ResourceManager& resourceManager)
    : mSpeed(PLAYER_SPEED) // Устанавливаем скорость игрока
    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)
{
    mSprite.setTexture(resourceManager.getTexture("player"));
    mSprite.setPosition(400.f, 300.f); // Начальная позиция игрока
}


Player::~Player() {
    // Освобождение ресурсов, если необходимо
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

    mSprite.move(movement * deltaTime.asSeconds()); // Перемещение игрока
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