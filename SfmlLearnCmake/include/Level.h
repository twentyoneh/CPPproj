#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"

class Level : public sf::Drawable {
public:
    Level();
    Level(ResourceManager& resourceManager);
    ~Level();

    void loadFromFile(const std::string& filename); // �������� ������ �� �����
    void update(sf::Time deltaTime); // ���������� ��������� ������
    void handleInput(); // ��������� �����

    void addEnemy(const Enemy& enemy); // ���������� ����� �� �������
    void setPlayer(const Player& player); // ��������� ������ �� �������
    Player& getPlayer(); // ��������� ������ �� ������

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Player mPlayer;
    std::vector<Enemy> mEnemies; // ������ ������ �� ������
    //sf::Texture mBackgroundTexture; // �������� ���� ������
    sf::Sprite mBackgroundSprite; // ������ ���� ������
};
