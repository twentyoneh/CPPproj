#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

#define PLAYER_SPEED 200.0f

class Player : public sf::Drawable, public sf::Transformable {
public:
    Player();
    Player(ResourceManager& resourceManager);
    ~Player();

    void update(sf::Time deltaTime);
    void moveUp(bool isMoving);
    void moveDown(bool isMoving);
    void moveLeft(bool isMoving);
    void moveRight(bool isMoving);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite mSprite;
    sf::Texture mTexture;
    float mSpeed;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};
