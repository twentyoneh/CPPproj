#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    
    ResourceManager(std::unordered_map<std::string, std::string> fileNameList);
    // ��������� �������� �� �����, ���� ��� ��� �� ���������
    static void loadTexture(const std::string& name, const std::string& filename);

    static void loadFont(const std::string& name, const std::string& filename);
    // ���������� ������ �� ����������� ��������
    sf::Texture& getTexture(const std::string& name);

    sf::Font& getFont(const std::string& name);

private:
    // ��������� ��� �������� �������
    static std::unordered_map<std::string, sf::Texture> textures;
    static std::unordered_map<std::string, sf::Font> fonts;
};