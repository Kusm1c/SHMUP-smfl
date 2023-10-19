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
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		sprite->move(0, 0.1);
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
struct Bullet
{
	sf::Sprite sprite;
	bool active;
	float velocity;
	bool enemy;
};

struct Enemy 
{
	bool active;
	sf::Sprite sprite;
	float velocity;
	bool canShoot;
	float shootTimer;
};


void updateBullets(Bullet(* bullets)[100], sf::RenderWindow* window, sf::Sprite* sprite)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		for (int i = 0; i < 100; i++)
		{
			if (!(*bullets)[i].active)
			{
				(*bullets)[i].active = true;
				(*bullets)[i].sprite.setPosition(sprite->getPosition());
				(*bullets)[i].enemy = false;
				break;
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if ((*bullets)[i].active)
		{
			window->draw((*bullets)[i].sprite);
			if ((*bullets)[i].enemy)
			{
				(*bullets)[i].sprite.move(-(*bullets)[i].velocity, 0);
			}
			else
			{
				(*bullets)[i].sprite.move((*bullets)[i].velocity, 0);
			}
			if ((*bullets)[i].sprite.getPosition().x > window->getSize().x)
			{
				(*bullets)[i].active = false;
			}
		}
	}
}
void updateEnemies(Enemy(* enemies)[10], sf::RenderWindow* window, sf::Sprite* sprite, Bullet(* bullets)[100])
{
	//Spawn 1 enemy randomly per second the one that can shoot will shoot every 2 seconds
	for (int i = 0; i < 10; i++)
	{
		if (!(*enemies)[i].active)
		{
			(*enemies)[i].active = true;
			(*enemies)[i].sprite.setPosition(window->getSize().x, rand() % window->getSize().y);
			break;
		}
	}
	//Move enemies
	for (int i = 0; i < 10; i++)
	{
		if ((*enemies)[i].active)
		{
			window->draw((*enemies)[i].sprite);
			(*enemies)[i].sprite.move(-(*enemies)[i].velocity, 0);
			if ((*enemies)[i].sprite.getPosition().x < 0)
			{
				(*enemies)[i].active = false;
			}
		}
	}
	//Shoot enemies
	for (int i = 0; i < 10; i++)
	{
		if ((*enemies)[i].active && (*enemies)[i].canShoot)
		{
			(*enemies)[i].shootTimer++;
			if ((*enemies)[i].shootTimer > 120)
			{
				(*enemies)[i].shootTimer = 0;
				for (int j = 0; j < 10; j++)
				{
					if (!(*bullets)[j].active)
					{
						(*bullets)[j].active = true;
						(*bullets)[j].sprite.setPosition((*enemies)[i].sprite.getPosition());
						(*bullets)[j].enemy = true;
						float dx = (*bullets)[j].sprite.getPosition().x - sprite->getPosition().x;
						float dy = (*bullets)[j].sprite.getPosition().y - sprite->getPosition().y;
						float angle = atan2(dy, dx);
						(*bullets)[j].sprite.setRotation(angle * 180 / 3.14159265);
						(*bullets)[j].velocity = 0.1;
						break;
					}
				}
			}
		}
	}
	
}

int main()
{
	//AllSprites address
	sf::Sprite* allSprites[300];


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


	//bullets
	sf::Texture bulletTexture;

	if (!bulletTexture.loadFromFile("img/Bullet.png"))
	{
		return 1;
	}
	Bullet bullets[100];
	for (int i = 0; i < 100; i++)
	{
		bullets[i].sprite.setTexture(bulletTexture);
		bullets[i].sprite.setOrigin(bulletTexture.getSize().x / 2, bulletTexture.getSize().y / 2);
		bullets[i].active = false;
		bullets[i].velocity = 0.1;
		allSprites[i + 3] = &bullets[i].sprite;
	}

	//Enemies make 50 enemies that can shoot and 50 that can't
	sf::Texture enemyTextureCanShoot;
	sf::Texture enemyTextureCantShoot;

	if (!enemyTextureCanShoot.loadFromFile("img/cruiser.png"))
	{
		return 1;
	}
	if (!enemyTextureCantShoot.loadFromFile("img/asteroid.png"))
	{
		return 1;
	}

	Enemy enemies[10];
	for (int i = 0; i < 10; i++)
	{
		enemies[i].sprite.setTexture(enemyTextureCanShoot);
		enemies[i].sprite.setOrigin(enemyTextureCanShoot.getSize().x / 2, enemyTextureCanShoot.getSize().y / 2);
		enemies[i].active = false;
		enemies[i].velocity = 0.1;
		enemies[i].canShoot = true;
		enemies[i].shootTimer = 0;
		allSprites[i + 103] = &enemies[i].sprite;
	}
	// for (int i = 0; i < 5; i++)
	// {
	// 	enemies[i].sprite.setTexture(enemyTextureCantShoot);
	// 	enemies[i].sprite.setOrigin(enemyTextureCantShoot.getSize().x / 2, enemyTextureCantShoot.getSize().y / 2);
	// 	enemies[i].active = false;
	// 	enemies[i].velocity = 0.1;
	// 	enemies[i].canShoot = false;
	// 	enemies[i].shootTimer = 0;
	// 	allSprites[i + 107] = &enemies[i].sprite;
	// }

	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				for (auto& bullet : bullets)
				{
					bullet.active = false;
				}
				window.close();
			}
		}

		window.clear();
		updateBackground(&backgroundSprite, &backgroundSprite2, backgroundHeight);
		movePlayerShip(&playerShipSprite);
		window.draw(backgroundSprite);
		window.draw(backgroundSprite2);
		window.draw(playerShipSprite);
		updateBullets(&bullets, &window, &playerShipSprite);
		updateEnemies(&enemies, &window, &playerShipSprite, &bullets);
		window.display();
	}

	return 0;
}
