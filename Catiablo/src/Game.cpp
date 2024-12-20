#include "../inc/Game.h"

Game::Game(sf::RenderWindow& window)
    : m_window(window),
      m_player("../../assets/textures/player.png"),
      m_monster("../../assets/textures/monster.png", sf::Vector2f(100, 100)),
      m_map("../../assets/textures/tileset.png", {{0, 1, 1, 0}, {1, 1, 1, 1}, {0, 1, 1, 0}}, window.getSize()) {}

void Game::run() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void Game::update(float deltaTime) {
    m_player.handleInput();
    m_player.update(deltaTime);
    m_monster.update(deltaTime, m_player.getPosition());
}

void Game::render() {
    m_window.clear();
    m_map.draw(m_window);
    m_player.draw(m_window);
    m_monster.draw(m_window);
    m_window.display();
}