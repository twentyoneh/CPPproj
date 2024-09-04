#include "Level.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

Level::Level() {
    // �������� �������� ���� �� ���������
    if (!mBackgroundTexture.loadFromFile("assets/images/background.png")) {
        throw std::runtime_error("Failed to load background texture");
    }
    mBackgroundSprite.setTexture(mBackgroundTexture);
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
    // ��������� ��������� ���� ������
    for (auto& enemy : mEnemies) {
        enemy.update(deltaTime);
    }

    // ��������� ��������� ������
    mPlayer.update(deltaTime);
}

void Level::handleInput() {
    // ��������� ����� ������������
    // ��������, ���������� ����������� �������� ������
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        mPlayer.moveUp(true);
    }
    else {
        mPlayer.moveUp(false);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        mPlayer.moveDown(true);
    }
    else {
        mPlayer.moveDown(false);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mPlayer.moveLeft(true);
    }
    else {
        mPlayer.moveLeft(false);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mPlayer.moveRight(true);
    }
    else {
        mPlayer.moveRight(false);
    }
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