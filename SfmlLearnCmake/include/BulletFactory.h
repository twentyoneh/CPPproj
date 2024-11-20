#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "../include/Bullet.h"
#include "../include/Fireball.h"

class BulletFactory
{
public:
    static std::shared_ptr<Bullet> makeBullet(sf::Vector2f pos, sf::Vector2f origin);   //типо создаёт shared_ptr на Bullet 
};