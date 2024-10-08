#include "Level.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

Level::Level() {

}

Level::Level(ResourceManager& resourceManager)
{
    mBackgroundSprite.setTexture(resourceManager.getTexture("background"));
}

Level::~Level() {
    // Освобождение ресурсов, если необходимо
}

void Level::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open level file: " + filename);
    }

    // Пример загрузки уровня
    std::string line;
    while (std::getline(file, line)) {
        // Здесь могла бы быть логика загрузки врагов, объектов и т.д.
        std::cout << "Reading line from file: " << line << std::endl;
    }

    file.close();
}

void Level::update(sf::Time deltaTime) {
    
}

void Level::addEnemy(const Enemy& enemy) {
    mEnemies.push_back(enemy);
}

void Level::setPlayer(const Player& player) {
    mPlayer = player;
}

Player& Level::getPlayer() {
    return mPlayer;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Сначала рисуем фон
    target.draw(mBackgroundSprite, states);

    // Затем всех врагов
    for (const auto& enemy : mEnemies) {
        target.draw(enemy, states);
    }

    // И наконец игрока
    target.draw(mPlayer, states);
}