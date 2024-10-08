#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"

enum class GameState {
    Menu,
    Playing,
    Paused,
    GameOver
};

class Level : public sf::Drawable {
public:
    Level(ResourceManager& resourceManager);
    ~Level();

    // �������� ������� ������
    void loadFromFile(const std::string& filename);  // �������� ������ �� �����
    void update(sf::Time deltaTime);  // ���������� ������ ������

    void addEnemy(const Enemy& enemy);  // ���������� ����� �� �������
    void setPlayer(const Player& player);  // ��������� ������ �� �������
    Player& getPlayer();  // ��������� ������

    void setGameState(GameState state);  // ��������� ��������� ������
    GameState getGameState() const;  // ��������� �������� ��������� ������

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // ���������� ���������� ������
    Player mPlayer;  // �����
    std::vector<Enemy> mEnemies;  // �����
    sf::Sprite mBackgroundSprite;  // ��� ������
    GameState mGameState;  // ��������� ������
};
