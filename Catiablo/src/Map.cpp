#include "../inc/Map.h"

Map::Map(const std::string& tilesetPath, const std::vector<std::vector<int>>& layout) {
    if (!m_tileset.loadFromFile(tilesetPath)) {
        throw std::runtime_error("Не удалось загрузить тайлсет");
    }

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(layout.size() * layout[0].size() * 4);

    for (size_t i = 0; i < layout.size(); ++i) {
        for (size_t j = 0; j < layout[i].size(); ++j) {
            int tileNumber = layout[i][j];
            int tu = tileNumber % (m_tileset.getSize().x / 32);
            int tv = tileNumber / (m_tileset.getSize().x / 32);

            sf::Vertex* quad = &m_vertices[(i * layout[0].size() + j) * 4];
            quad[0].position = sf::Vector2f(j * 32, i * 32);
            quad[1].position = sf::Vector2f((j + 1) * 32, i * 32);
            quad[2].position = sf::Vector2f((j + 1) * 32, (i + 1) * 32);
            quad[3].position = sf::Vector2f(j * 32, (i + 1) * 32);

            quad[0].texCoords = sf::Vector2f(tu * 32, tv * 32);
            quad[1].texCoords = sf::Vector2f((tu + 1) * 32, tv * 32);
            quad[2].texCoords = sf::Vector2f((tu + 1) * 32, (tv + 1) * 32);
            quad[3].texCoords = sf::Vector2f(tu * 32, (tv + 1) * 32);
        }
    }
}

void Map::draw(sf::RenderWindow& window) {
    sf::RenderStates states;
    states.texture = &m_tileset;
    window.draw(m_vertices, states);
}
