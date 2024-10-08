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
    // ������������ ��������, ���� ����������
}

void Level::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open level file: " + filename);
    }

    // ������ �������� ������
    std::string line;
    while (std::getline(file, line)) {
        // ����� ����� �� ���� ������ �������� ������, �������� � �.�.
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
    // ������� ������ ���
    target.draw(mBackgroundSprite, states);

    // ����� ���� ������
    for (const auto& enemy : mEnemies) {
        target.draw(enemy, states);
    }

    // � ������� ������
    target.draw(mPlayer, states);
}