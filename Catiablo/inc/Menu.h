#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void display();                    // Отображение меню
    int handleInput();                 // Обработка ввода (возвращает выбор)
    
private:
    sf::RenderWindow& m_window;        // Ссылка на окно
    sf::Font m_font;                   // Шрифт для текста
    std::vector<sf::Text> m_options;   // Опции меню
    int m_selectedIndex;               // Выбранный пункт меню
    sf::Texture m_imagne;
    sf::Sprite m_background;               

    void draw();                       // Рисование меню
    void moveUp();                     // Навигация вверх
    void moveDown();                   // Навигация вниз
};

#endif // MENU_H
