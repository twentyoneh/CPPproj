#include "../inc/Menu.h"

Menu::Menu(sf::RenderWindow& window) : m_window(window), m_selectedIndex(0) {
    // Загружаем шрифт
    if (!m_font.loadFromFile("assets/textures/Secession.ttf")) {
        throw std::runtime_error("Не удалось загрузить шрифт");
    }

    if (!m_imagne.loadFromFile("assets/textures/menu_bg.png")) {
        throw std::runtime_error("Не удалось загрузить бэк");
    }
    m_background.setTexture(m_imagne);

    // Добавляем опции меню
    std::vector<std::string> options = {"Play", "Settings", "Exit"};
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(m_font);
        text.setString(options[i]);
        text.setCharacterSize(40);
        text.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White); // Первый пункт выделен
        text.setPosition(300, 200 + i * 60); // Расположение пунктов
        m_options.push_back(text);
    }
}

void Menu::display() {
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    moveUp();
                } else if (event.key.code == sf::Keyboard::Down) {
                    moveDown();
                } else if (event.key.code == sf::Keyboard::Enter) {
                    return; // Выбор сделан
                }
            }
        }

        draw();
    }
}

int Menu::handleInput() {
    // Возвращаем индекс выбранного пункта
    return m_selectedIndex;
}

void Menu::draw() {
    m_window.clear();
    sf::Vector2u windowSize = m_window.getSize();
    sf::Vector2u textureSize = m_imagne.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    m_background.setScale(scaleX, scaleY);

    m_window.draw(m_background);
    for (const auto& option : m_options) {
        m_window.draw(option);
    }
    m_window.display();
}

void Menu::moveUp() {
    if (m_selectedIndex > 0) {
        m_options[m_selectedIndex].setFillColor(sf::Color::White);
        m_selectedIndex--;
        m_options[m_selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (m_selectedIndex < m_options.size() - 1) {
        m_options[m_selectedIndex].setFillColor(sf::Color::White);
        m_selectedIndex++;
        m_options[m_selectedIndex].setFillColor(sf::Color::Yellow);
    }
}
