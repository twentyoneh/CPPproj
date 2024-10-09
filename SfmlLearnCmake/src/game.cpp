#include "Game.h"

Game::Game()
    : mWindow(sf::VideoMode(mWidth, mHeight), "SFML Game")
    , mResourceManager(mfileNameList)
    , mPlayer(mResourceManager)
    , mLevel(mResourceManager)
    , mMenuState(mResourceManager, mWindow)
{
    mPlayer.setPosition(mWidth / 2.0f, mHeight / 2.0f);
}

Game::~Game() {
    // ќсвобождение ресурсов (если нужно)
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
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
        {
            handlePlayerInput(event.key.code, true);
            break;
        }
        case sf::Event::KeyReleased:
        {
            handlePlayerInput(event.key.code, false);
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (sf::Event::MouseButtonPressed == sf::Mouse::Button::Left) {
                handlePlayerMouse(sf::Mouse::Button::Left, true);
            }
            else if (sf::Event::MouseButtonPressed == sf::Mouse::Button::Right) {
                handlePlayerMouse(sf::Mouse::Button::Right, true);
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (sf::Event::MouseButtonReleased == sf::Mouse::Button::Left) {
                handlePlayerMouse(sf::Mouse::Button::Left, false);
            }
            else if (sf::Event::MouseButtonReleased == sf::Mouse::Button::Right) {
                handlePlayerMouse(sf::Mouse::Button::Right, false);
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            handlePlayerMouse(sf::Mouse::getPosition(mWindow)); //получаем позицию мышки
            break;
        }
        case sf::Event::Closed:
        {
            mWindow.close();
            break;
        }
        }
    }
}

void Game::update(sf::Time deltaTime) {
    mPlayer.update(deltaTime);
    // ќбновление логики врагов, пуль, уровней и т.д.
    /*for (auto& enemy : mEnemies) {
        enemy.update(deltaTime);
    }*/
    mLevel.update(deltaTime);
    // Ћогика столкновений, обновление состо€ни€ игры и т.д.
}

void Game::render() {
    mWindow.clear();
    if (mLevel.getGameState() == GameState::Menu) 
    {
        mMenuState.draw();
    } 
    else if(mLevel.getGameState() == GameState::Playing)
    {
        mWindow.draw(mLevel);
        mWindow.draw(mPlayer);
        /*for (const auto& enemy : mEnemies) {
            mWindow.draw(enemy);
        }*/
    }
        // ќтрисовка других игровых объектов
        mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if(mLevel.getGameState() == GameState::Playing)
    {
        if (key == sf::Keyboard::W)
            mPlayer.moveUp(isPressed);
        else if (key == sf::Keyboard::S)
            mPlayer.moveDown(isPressed);
        else if (key == sf::Keyboard::A)
            mPlayer.moveLeft(isPressed);
        else if (key == sf::Keyboard::D)
            mPlayer.moveRight(isPressed);
    } 
    else if(mLevel.getGameState() == GameState::Menu)
    {
        if (key == sf::Keyboard::W)
            mMenuState.moveUp();
        else if (key == sf::Keyboard::S)
            mMenuState.moveDown();
        else if (key == sf::Keyboard::Enter)
            mLevel.setGameState(GameState::Playing);
    }
    // ќбработка других клавиш и действий
}

void Game::handlePlayerMouse(sf::Mouse::Button key, bool isPressed)
{

}

void Game::handlePlayerMouse(sf::Vector2i pos)
{
    mMousePosition = pos;
    mPlayer.setMousePos(mMousePosition);
    //mDeltaMousePosition = mLastMousePosition Ц mMousePosition;
    //mLastMousePosition = mMousePosition;
}
