#include "MenuState.h"

MenuState::MenuState(ResourceManager& resourceManager, sf::RenderWindow& window)
    : mWindow(window), mSelectedItemIndex(0)
{
    // Загружаем шрифт из ресурс-менеджера
    mFont = resourceManager.getFont("main_font");

    // Настройка пунктов меню
    sf::Text startGame;
    startGame.setFont(mFont);
    startGame.setString("Start Game");
    startGame.setFillColor(sf::Color::Red);  // Выбранный пункт выделен красным
    startGame.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 - 30);

    sf::Text exit;
    exit.setFont(mFont);
    exit.setString("Exit");
    exit.setFillColor(sf::Color::White);
    exit.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 + 30);

    mMenuItems.push_back(startGame);
    mMenuItems.push_back(exit);
}

void MenuState::draw() {
    for (const auto& item : mMenuItems) {
        mWindow.draw(item);
    }
}

void MenuState::moveUp() {
    if (mSelectedItemIndex > 0) {
        mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::White);
        mSelectedItemIndex--;
        mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::Red);  // Новый выбранный пункт
    }
}

void MenuState::moveDown() {
    if (mSelectedItemIndex < mMenuItems.size() - 1) {
        mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::White);
        mSelectedItemIndex++;
        mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::Red);  // Новый выбранный пункт
    }
}

int MenuState::getSelectedItem() const
{
    return mSelectedItemIndex;
}

