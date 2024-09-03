#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
// ������ ����������� ������������ �����

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void loadResources();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow mWindow;
    ResourceManager mResourceManager;
    Player mPlayer;
    std::vector<Enemy> mEnemies;
    Level mLevel;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    // ������ ����������� ���������� � �������
};


