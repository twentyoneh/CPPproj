#include "Game.h"

Game::Game()
    : mWindow(sf::VideoMode(mWidth, mHeight), "SFML Game")
    , mfileNameList{ mfileNameList.insert({"player", "../../../assets/images/player.png",
        "player", "../../../assets/images/player.png",
        "player", "../../../assets/images/player.png"}) } //надо как-то это зафиксить
    , mResourceManager(mfileNameList)
    , mPlayer(mResourceManager)
    , mLevel()
{
    loadResources();
    mPlayer.setPosition(mWidth / 2.0f, mHeight / 2.0f);
}

Game::~Game() {
    // Освобождение ресурсов (если нужно)
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    mPlayer.update(deltaTime);
    // Обновление логики врагов, пуль, уровней и т.д.
    for (auto& enemy : mEnemies) {
        enemy.update(deltaTime);
    }
    mLevel.update(deltaTime);
    // Логика столкновений, обновление состояния игры и т.д.
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mLevel);
    mWindow.draw(mPlayer);
    for (const auto& enemy : mEnemies) {
        mWindow.draw(enemy);
    }
    // Отрисовка других игровых объектов
    mWindow.display();
}

void Game::loadResources() {
    // Загрузка текстур, звуков и шрифтов через ResourceManager
    mResourceManager.loadTexture("player", "../../../assets/images/player.png");
    mResourceManager.loadTexture("enemy", "../../../assets/images/enemy.png");
    mResourceManager.loadFont("main_font", "../../../assets/fonts/arial.ttf");
    // Загрузка других ресурсов
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        mPlayer.moveUp(isPressed);
    else if (key == sf::Keyboard::S)
        mPlayer.moveDown(isPressed);
    else if (key == sf::Keyboard::A)
        mPlayer.moveLeft(isPressed);
    else if (key == sf::Keyboard::D)
        mPlayer.moveRight(isPressed);
    // Обработка других клавиш и действий
}
