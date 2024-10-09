#pragma once
#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable {
public:
    Enemy();
    virtual ~Enemy();

    // Обновление логики врага, можно переопределить в производных классах
    virtual void update(sf::Time deltaTime);

    // Установка позиции врага
    void setPosition(const sf::Vector2f& position);

    // Нанесение урона врагу
    void takeDamage(int damage);

    // Проверка, мертв ли враг
    bool isDead() const;

protected:
    int mHealth;  // Здоровье врага
    sf::Sprite mSprite;  // Спрайт врага

private:
    // Отрисовка врага
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
