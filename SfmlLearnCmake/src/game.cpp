#include "Game.h"

Game::Game()
    : mWindow(sf::VideoMode(800, 600), "SFML Game")
    , mPlayer()
    , mLevel()
{
    loadResources();
    mPlayer.setPosition(100.f, 100.f);
}

Game::~Game() {
    // ������������ �������� (���� �����)
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
    // ���������� ������ ������, ����, ������� � �.�.
    for (auto& enemy : mEnemies) {
        enemy.update(deltaTime);
    }
    mLevel.update(deltaTime);
    // ������ ������������, ���������� ��������� ���� � �.�.
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mLevel);
    mWindow.draw(mPlayer);
    for (const auto& enemy : mEnemies) {
        mWindow.draw(enemy);
    }
    // ��������� ������ ������� ��������
    mWindow.display();
}

void Game::loadResources() {
    // �������� �������, ������ � ������� ����� ResourceManager
    mResourceManager.loadTexture("player", "assets/images/player.png");
    mResourceManager.loadTexture("enemy", "assets/images/enemy.png");
    mResourceManager.loadFont("main_font", "assets/fonts/arial.ttf");
    // �������� ������ ��������
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
    // ��������� ������ ������ � ��������
}
