#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "MenuState.h"
// Другие необходимые заголовочные файлы

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void handlePlayerMouse(sf::Mouse::Button key, bool isPressed);
    void handlePlayerMouse(sf::Vector2i pos);
    
    
    // Заполнение mfileNameList
    std::map<std::string, std::string> mfileNameList{
        {"player", "../../../assets/images/player.png" },
        {"enemy","../../../assets/images/enemy.png"},
        {"main_font","../../../assets/fonts/ArialRegular.ttf"},
        {"background","../../../assets/images/background.jpg"},
        {"backgroundMenu","../../../assets/images/backgroundMenu.jpg"}
    };
    

    sf::RenderWindow mWindow;
    ResourceManager mResourceManager;
    Player mPlayer;
    std::vector<Enemy> mEnemies;
    Level mLevel;
    MenuState mMenuState;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    static const unsigned int mWidth = 800, mHeight = 600;
    sf::Vector2i mMousePosition;
    //sf::Vector2i mDeltaMousePosition{};
    //sf::Vector2i mLastMousePosition{};

    // Другие необходимые переменные и объекты
};


