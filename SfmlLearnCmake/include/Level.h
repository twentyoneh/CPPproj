#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"

enum class GameState {
    Menu,
    Playing,
    Paused,
    GameOver
};

class Level : public sf::Drawable {
public:
    Level(ResourceManager& resourceManager);
    ~Level();

    // Основные функции уровня
    void loadFromFile(const std::string& filename);  // Загрузка уровня из файла
    void update(sf::Time deltaTime);  // Обновление логики уровня

    void addEnemy(const Enemy& enemy);  // Добавление врага на уровень
    void setPlayer(const Player& player);  // Установка игрока на уровень
    Player& getPlayer();  // Получение игрока

    void setGameState(GameState state);  // Установка состояния уровня
    GameState getGameState() const;  // Получение текущего состояния уровня

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Внутренние переменные уровня
    Player mPlayer;  // Игрок
    std::vector<Enemy> mEnemies;  // Враги
    sf::Sprite mBackgroundSprite;  // Фон уровня
    GameState mGameState;  // Состояние уровня
};
