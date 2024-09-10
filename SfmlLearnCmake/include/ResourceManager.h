#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    
    ResourceManager(std::map<std::string, std::string> fileNameList);
    // ��������� �������� �� �����, ���� ��� ��� �� ���������
    void loadTexture(const std::string& name, const std::string& filename);

    void loadFont(const std::string& name, const std::string& filename);
    // ���������� ������ �� ����������� ��������
    sf::Texture& getTexture(const std::string& name);

    sf::Font& getFont(const std::string& name);

private:
    // ��������� ��� �������� �������
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
};