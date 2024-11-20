#pragma once

#include<SFML/Graphics.hpp>
#include "ResourceManager.h"

class MenuState {
public:
    MenuState(sf::RenderWindow& window);

    // Основные функции меню
    void draw();  // Отрисовка меню
    void moveUp();  // Перемещение вверх по меню
    void moveDown();  // Перемещение вниз по меню
    int getSelectedItem() const;  // Получение выбранного элемента меню

private:
    sf::Font mFont;  // Шрифт для текста меню
    std::vector<sf::Text> mMenuItems;  // Элементы меню
    int mSelectedItemIndex;  // Индекс выбранного элемента
    sf::RenderWindow& mWindow;  // Ссылка на окно для отрисовки
};
