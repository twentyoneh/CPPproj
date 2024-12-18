#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

#define PLAYER_SPEED 200.0f

class Player : public sf::Drawable, public sf::Transformable {
public:
    Player();
    ~Player();

    void update(sf::Time deltaTime);
    void moveUp(bool isMoving);
    void moveDown(bool isMoving);
    void moveLeft(bool isMoving);
    void moveRight(bool isMoving);
    void setMousePos(sf::Vector2i pos);
    sf::Vector2f getCurrentPos();
    sf::Vector2f getOrigin();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void CharacterMove(sf::Vector2f movement, sf::Time deltaTime);
    void CharacterRotate();

    sf::Sprite mSprite;
    sf::Texture mTexture;
    float mSpeed;
    sf::Vector2i mMousePosition{};
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};
