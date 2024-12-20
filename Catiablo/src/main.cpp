#include <SFML/Graphics.hpp>
#include "../inc/Menu.h"
#include "../inc/Game.h"

enum class GameState {
    Menu,
    Playing,
    Settings,
    Exit
};


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Diablo-like Game");

    // Показать меню
    GameState state = GameState::Menu;
    Menu menu(window);
    Game game(window);

    while (window.isOpen()) {
        if (state == GameState::Menu) {
            menu.display();
            int choice = menu.handleInput();
            if (choice == 0) {
                state = GameState::Playing; // Переход в игровой процесс
            } else if (choice == 1) {
                state = GameState::Settings; // Пока что можно оставить пустым
            } else if (choice == 2) {
                state = GameState::Exit;
                window.close();
            }
        } else if (state == GameState::Playing) {
            // Запуск игрового процесса
            game.run();
            state = GameState::Menu; // Возврат в меню после завершения игры
        }
    }


    return 0;
}
