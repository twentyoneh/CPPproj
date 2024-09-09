#include "Game.h"

Game::Game()
    : mWindow(sf::VideoMode(mWidth, mHeight), "SFML Game")
    , mfileNameList{ mfileNameList.insert({"player", "../../../assets/images/player.png",
        "player", "../../../assets/images/player.png",
        "player", "../../../assets/images/player.png"}) } //���� ���-�� ��� ���������
    , mResourceManager(mfileNameList)
    , mPlayer(mResourceManager)
    , mLevel()
{
    loadResources();
    mPlayer.setPosition(mWidth / 2.0f, mHeight / 2.0f);
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
    mResourceManager.loadTexture("player", "../../../assets/images/player.png");
    mResourceManager.loadTexture("enemy", "../../../assets/images/enemy.png");
    mResourceManager.loadFont("main_font", "../../../assets/fonts/arial.ttf");
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
