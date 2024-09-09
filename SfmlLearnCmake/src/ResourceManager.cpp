#include "ResourceManager.h"

ResourceManager::ResourceManager(std::unordered_map<std::string, std::string> fileNameList)
{

}

void ResourceManager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
		throw std::runtime_error("ResourceManager::loadTexture - Failed to load " + filename);
	textures[name] = texture;
}

void ResourceManager::loadFont(const std::string& name, const std::string& filename)
{
	sf::Font font;
	if (!font.loadFromFile(filename))
		throw std::runtime_error("ResourceManager::loadFont - Failed to load " + filename);
	fonts[name] = font;
}

sf::Texture& ResourceManager::getTexture(const std::string& name)
{
	return textures[name];
}

sf::Font& ResourceManager::getFont(const std::string& name)
{
	return fonts[name];
}
