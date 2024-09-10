#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    
    ResourceManager(std::map<std::string, std::string> fileNameList);
    // Загружает текстуру из файла, если она еще не загружена
    void loadTexture(const std::string& name, const std::string& filename);

    void loadFont(const std::string& name, const std::string& filename);
    // Возвращает ссылку на загруженную текстуру
    sf::Texture& getTexture(const std::string& name);

    sf::Font& getFont(const std::string& name);

private:
    // Контейнер для хранения текстур
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
};