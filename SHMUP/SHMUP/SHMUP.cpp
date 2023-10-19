#include <SFML/Graphics.hpp>


void movePlayerShip(sf::Sprite* sprite)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sprite->move(-0.1, 0);
		sprite->setRotation(270);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprite->move(0.1, 0);
		sprite->setRotation(90);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		sprite->move(0, -0.1);
		sprite->setRotation(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		sprite->move(0, 0.1);
		sprite->setRotation(180);
	}
}

int main()
{

	//AllSprites address
	sf::Sprite* allSprites[100];


	//Player Ship
	sf::Texture playerShipTexture;

	if (!playerShipTexture.loadFromFile("PlayerShip.png"))
	{
		return 1;
	}
	int width = playerShipTexture.getSize().x;
	int height = playerShipTexture.getSize().y;
	sf::Sprite playerShipSprite;
	playerShipSprite.setOrigin(width / 2, height / 2);
	playerShipSprite.setRotation(90);
	playerShipSprite.setTexture(playerShipTexture);
	allSprites[0] = &playerShipSprite;


	//Background
	sf::Texture backgroundTexture;

	if (!backgroundTexture.loadFromFile("Background.png"))
	{
		return 1;
	}
	int backgroundWidth = backgroundTexture.getSize().x;
	int backgroundHeight = backgroundTexture.getSize().y;
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);
	width = backgroundTexture.getSize().x;
	height = backgroundTexture.getSize().y;
	allSprites[1] = &backgroundSprite;
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
	playerShipSprite.setPosition(window.getSize().x / 4, window.getSize().y / 2);




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(backgroundSprite);
		movePlayerShip(&playerShipSprite);
		window.draw(playerShipSprite);
		window.display();
	}

	return 0;
}
