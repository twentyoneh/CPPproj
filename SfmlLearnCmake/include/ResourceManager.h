#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    
    static sf::Texture& getTexture(const std::string& name);

    static sf::Font& getFont(const std::string& name);

    static ResourceManager& getInstance();
private:

    // Загружает текстуру из файла, если она еще не загружена
    void loadTexture(const std::string& name, const std::string& filename);

    void loadFont(const std::string& name, const std::string& filename);
    // Возвращает ссылку на загруженную текстуру
    static std::map<std::string, std::string> mfileNameList;
    ResourceManager();
    ~ResourceManager();
    // Контейнер для хранения текстур
    static std::unordered_map<std::string, sf::Texture> textures;
    static std::unordered_map<std::string, sf::Font> fonts;
};