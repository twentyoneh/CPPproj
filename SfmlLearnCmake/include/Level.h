#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"

class Level : public sf::Drawable {
public:
    Level();
    Level(ResourceManager& resourceManager);
    ~Level();

    void loadFromFile(const std::string& filename); // Загрузка уровня из файла
    void update(sf::Time deltaTime); // Обновление состояния уровня
    void handleInput(); // Обработка ввода

    void addEnemy(const Enemy& enemy); // Добавление врага на уровень
    void setPlayer(const Player& player); // Установка игрока на уровень
    Player& getPlayer(); // Получение ссылки на игрока

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Player mPlayer;
    std::vector<Enemy> mEnemies; // Список врагов на уровне
    //sf::Texture mBackgroundTexture; // Текстура фона уровня
    sf::Sprite mBackgroundSprite; // Спрайт фона уровня
};
