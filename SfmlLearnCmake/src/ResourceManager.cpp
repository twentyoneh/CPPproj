#include "ResourceManager.h"

std::unordered_map<std::string, sf::Texture> ResourceManager::textures;
std::unordered_map<std::string, sf::Font> ResourceManager::fonts;
// Заполнение mfileNameList
std::map<std::string, std::string> ResourceManager::mfileNameList{
	{"player", "../../../assets/images/player.png" },
	{"enemy","../../../assets/images/enemy.png"},
	{"main_font","../../../assets/fonts/ArialRegular.ttf"},
	{"background","../../../assets/images/background.jpg"},
	{"backgroundMenu","../../../assets/images/backgroundMenu.jpg"},
	{"fireball","../../../assets/images/fireball.png"}
};

ResourceManager::ResourceManager()
{
	for (const auto& pair : ResourceManager::mfileNameList) {
		if (pair.first == "main_font") 
		{
			loadFont(pair.first, pair.second);
		}
		else
		{
			loadTexture(pair.first, pair.second);
		}

	}
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

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

ResourceManager::~ResourceManager()
{
}
