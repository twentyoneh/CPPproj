#include "Level.h"

Level::Level(ResourceManager& resourceManager)
    : mGameState(GameState::Menu)  // Начальное состояние — меню
{
    mBackgroundSprite.setTexture(resourceManager.getTexture("background"));
}

Level::~Level() {
    // Освобождение ресурсов (если нужно)
}

void Level::update(sf::Time deltaTime) {
    if (mGameState == GameState::Playing) {
        // Обновление игрока
        mPlayer.update(deltaTime);

        // Обновление всех врагов
        for (auto& enemy : mEnemies) {
            enemy.update(deltaTime);
        }
        //Удаление мертвых врагов (опционеально)
        //mEnemies.erase(std::remove_if(mEnemies.begin(), mEnemies.end(),
        //    [](std::unique_ptr<Enemy>& enemy) { return enemy->isDead(); }),
        //    mEnemies.end());
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
