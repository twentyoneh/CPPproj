#include "Player.h"

Player::Player()
{
}

Player::Player(ResourceManager& resourceManager)
    : mSpeed{ PLAYER_SPEED } // Устанавливаем скорость игрока
    , mMousePosition{ }
    , mIsMovingUp{ false }
    , mIsMovingDown{ false }
    , mIsMovingLeft{ false }
    , mIsMovingRight{ false }
{
    mSprite.setTexture(resourceManager.getTexture("player"));
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    mSprite.setPosition(400.f, 300.f); // Начальная позиция игрока
}

Player::~Player() {
    // Освобождение ресурсов, если необходимо
}

void Player::update(sf::Time deltaTime) 
{
    //printf("X: %f; Y: %f \n", heroPosition.x, heroPosition.y);

    CharacterMove(sf::Vector2f(0.0f, 0.0f), deltaTime);
    CharacterRotate();
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

void Player::setMousePos(sf::Vector2i pos)
{
    mMousePosition = pos;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void Player::CharacterMove(sf::Vector2f movement, sf::Time deltaTime)
{
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

void Player::CharacterRotate()
{
    sf::Vector2f heroPosition = mSprite.getPosition();

    float dx = mMousePosition.x - heroPosition.x;
    float dy = mMousePosition.y - heroPosition.y;

    float angle = atan2(dy, dx) * 180 / 3.14159;  // Перевод из радиан в градусы

    // Устанавливаем поворот героя
    mSprite.setRotation(angle + 90);  // Плюс 90 градусов, чтобы герой смотрел вперед
}
