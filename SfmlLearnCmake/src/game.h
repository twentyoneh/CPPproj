#define GAME_H
#ifdef GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	bool mIsMovingUp{ 0 }, mIsMovingDown{ 0 }, mIsMovingLeft{ 0 }, mIsMovingRight{ 0 };

private:
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	float PlayerSpeed = 500.0f;
	sf::Time TimePerFrame = sf::seconds(1.0f/60.0f);
};

#endif // 
