#include <iostream>
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

void updateBackground(sf::Sprite* sprite, sf::Sprite* sprite2, float sizeHeight)
{
	sprite->move(-0.01, 0);
	sprite2->move(-0.01, 0);
	if (sprite->getPosition().x < -sizeHeight)
	{
		sprite->setPosition(sprite2->getPosition().x + sizeHeight, 0);
	}
	else if (sprite2->getPosition().x < -sizeHeight)
	{
		sprite2->setPosition(sprite->getPosition().x + sizeHeight, 0);
	}
}

int main()
{
	//AllSprites address
	sf::Sprite* allSprites[100];


	//Player Ship
	sf::Texture playerShipTexture;

	if (!playerShipTexture.loadFromFile("img/PlayerShip.png"))
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

	if (!backgroundTexture.loadFromFile("img/Background.png"))
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

	//Second Background
	sf::Texture backgroundTexture2;

	if (!backgroundTexture2.loadFromFile("img/Background.png"))
	{
		return 1;
	}
	backgroundWidth = backgroundTexture2.getSize().x;
	backgroundHeight = backgroundTexture2.getSize().y;
	sf::Sprite backgroundSprite2;
	backgroundSprite2.setTexture(backgroundTexture2);
	backgroundSprite2.setPosition(backgroundHeight, 0);
	allSprites[2] = &backgroundSprite2;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		updateBackground(&backgroundSprite, &backgroundSprite2, backgroundHeight);
		movePlayerShip(&playerShipSprite);
		window.draw(backgroundSprite);
		window.draw(backgroundSprite2);
		window.draw(playerShipSprite);
		window.display();
	}

	return 0;
}
