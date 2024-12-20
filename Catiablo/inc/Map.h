#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map(const std::string& tilesetPath, const std::vector<std::vector<int>>& layout);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture m_tileset;
    sf::VertexArray m_vertices;
};

#endif // MAP_H
