#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy : public sf::Drawable, public sf::Transformable, public Entity {
public:
    Enemy();
    ~Enemy();


    void update(sf::Time deltaTime);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void loadTexture();

    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mDirection; // Направление движения врага
};