#include "Level.h"

Level::Level(ResourceManager& resourceManager)
    : mGameState(GameState::Menu)  // ��������� ��������� � ����
{
    mBackgroundSprite.setTexture(resourceManager.getTexture("background"));
}

Level::~Level() {
    // ������������ �������� (���� �����)
}

void Level::loadFromFile(const std::string& filename) {
    // ������ �������� ������ �� �����
}

void Level::update(sf::Time deltaTime) {
    if (mGameState == GameState::Playing) {
        // ���������� ������
        mPlayer.update(deltaTime);

        // ���������� ���� ������
        for (auto& enemy : mEnemies) {
            enemy.update(deltaTime);
        }
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mBackgroundSprite, states);
    target.draw(mPlayer, states);

    for (const auto& enemy : mEnemies) {
        target.draw(enemy, states);
    }
}

void Level::addEnemy(const Enemy& enemy) {
    mEnemies.push_back(enemy);
}

void Level::setPlayer(const Player& player) {
    mPlayer = player;
}

Player& Level::getPlayer() {
    return mPlayer;
}

void Level::setGameState(GameState state) {
    mGameState = state;
}

GameState Level::getGameState() const {
    return mGameState;
}
