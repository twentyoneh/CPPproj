#include "BulletFactory.h"

std::shared_ptr<Bullet> BulletFactory::makeBullet(sf::Vector2f pos, sf::Vector2f origin)
{
        return std::make_shared<Fireball>(pos, origin);
}