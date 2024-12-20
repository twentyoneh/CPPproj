#include <SFML/Graphics.hpp>
#include "../inc/Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Diablo-like Game");

    Menu menu(window);

    // Показать меню
    menu.display();

    int choice = menu.handleInput();
    if (choice == 0) {
        // Логика для "Play"
    } else if (choice == 1) {
        // Логика для "Settings"
    } else if (choice == 2) {
        // Логика для "Exit"
        window.close();
    }

    return 0;
}
