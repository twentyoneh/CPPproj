#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    // Загружает текстуру из файла, если она еще не загружена
    sf::Texture& loadTexture(const std::string& name, const std::string& filename);

    sf::Texture& loadFont(const std::string& name, const std::string& filename);
    // Возвращает ссылку на загруженную текстуру
    sf::Texture& getTexture(const std::string& name);

private:
    // Контейнер для хранения текстур
    std::unordered_map<std::string, sf::Texture> textures;
};