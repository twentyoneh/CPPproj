#include "../inc/Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Diablo-like Game") {}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents(){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update()
{
}

void Game::render()
{
    window.clear();
    // Отрисовка объектов
    window.display();
}
