#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Monster.h"
#include "Map.h"



class Game {
public:
    Game(sf::RenderWindow& window);
    void run(); // Запускает игровой процесс

private:
    sf::RenderWindow& m_window;
    Player m_player;
    Monster m_monster;
    Map m_map;

    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_H
