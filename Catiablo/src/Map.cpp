#include "../inc/Map.h"

Map::Map(const std::string& tilesetPath, const std::vector<std::vector<int>>& layout, sf::Vector2u windowSize) {
    if (!m_tileset.loadFromFile(tilesetPath)) {
        throw std::runtime_error("Не удалось загрузить тайлсет");
    }

    m_vertices.setPrimitiveType(sf::Quads);

    sf::Vector2u tileSize(32, 32); // Размер одного тайла

    // Вычисляем количество тайлов по горизонтали и вертикали
    unsigned int tilesX = (windowSize.x + tileSize.x - 1) / tileSize.x; // Округление вверх
    unsigned int tilesY = (windowSize.y + tileSize.y - 1) / tileSize.y; // Округление вверх

    m_vertices.resize(tilesX * tilesY * 4);

    for (unsigned int i = 0; i < tilesY; ++i) {
        for (unsigned int j = 0; j < tilesX; ++j) {
            // Используем модуль для циклического заполнения тайлами
            int tileNumber = layout[i % layout.size()][j % layout[0].size()];
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            sf::Vertex* quad = &m_vertices[(i * tilesX + j) * 4];
            quad[0].position = sf::Vector2f(static_cast<float>(j * tileSize.x), static_cast<float>(i * tileSize.y));
            quad[1].position = sf::Vector2f(static_cast<float>((j + 1) * tileSize.x), static_cast<float>(i * tileSize.y));
            quad[2].position = sf::Vector2f(static_cast<float>((j + 1) * tileSize.x), static_cast<float>((i + 1) * tileSize.y));
            quad[3].position = sf::Vector2f(static_cast<float>(j * tileSize.x), static_cast<float>((i + 1) * tileSize.y));

            quad[0].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>(tv * tileSize.y));
            quad[1].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>(tv * tileSize.y));
            quad[2].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
            quad[3].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
        }
    }
}

void Map::draw(sf::RenderWindow& window) {
    sf::RenderStates states;
    states.texture = &m_tileset;
    window.draw(m_vertices, states);
}