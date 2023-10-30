#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
#include <windows.h>

int currentScore;
std::vector<int> leaderboardScores;

Game::Game() : window(sf::VideoMode(1280, 720), "SFML Game")
{
	playerTexture.loadFromFile("img/PlayerShip.png");
	bulletTexture.loadFromFile("img/Bullet.png");
	enemyTexture.loadFromFile("img/cruiser.png");
	asteroidTexture.loadFromFile("img/asteroid.png");
	backgroundTexture.loadFromFile("img/game_background_1/game_background_1.png");
	loadExplosionTextures();

	player = Player(playerTexture, 400, 300);


	setBulletsAndEnemiesAndBackGround();


	std::srand(std::time(0));
}

void Game::loadExplosionTextures()
{
	for (int i = 1; i <= 11; i++)
	{
		sf::Texture texture;
		std::string path = "img/explosion/boom" + std::to_string(i) + ".png";
		texture.loadFromFile(path);
		explosionTextures.push_back(texture);
	}
}

void Game::setBulletsAndEnemiesAndBackGround()
{
	bullets.reserve(100);
	enemies.reserve(100);


	for (int i = 0; i < 100; i++)
	{
		bullets.emplace_back(bulletTexture, -800, -800, false);
		if (i < 50)
		{
			enemies.emplace_back(asteroidTexture, -800, -800, false);
			enemies[i].setVelocity(0.3f);
		}
		else
		{
			enemies.emplace_back(enemyTexture, -800, -800, true);
			enemies[i].setVelocity(0.5f);
		}
		enemies[i].setActive(false);
	}
	pathToBackgrounds.clear();
	pathToBackgrounds = {
		"img/game_background_1/layers", "img/game_background_2/layers", "img/game_background_3/layers",
		"img/game_background_4/layers"
	};
	numberOfFilesInDirectory.clear();
	numberOfFilesInDirectory = {7, 9, 8, 5};

	int pathToBackground = rand() % 4;
	choosenBackgroundTextures.clear();
	choosenBackgroundTextures = loadBackgroundTextures(pathToBackground);

	choosenBackgroundSprites.clear();
	choosenBackgroundSprites.reserve(numberOfFilesInDirectory[pathToBackground]);
	for (int i = 0; i < numberOfFilesInDirectory[pathToBackground]; i++)
	{
		choosenBackgroundSprites.emplace_back(choosenBackgroundTextures[i]);
		choosenBackgroundSprites[i].setPosition(1280 * i/2, 0);
	}
}

void Game::run()
{
	stateManager.changeState(GameState::TitleScreen);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		switch (stateManager.getState())
		{
		case GameState::TitleScreen:
			handleTitleScreenInput();
			renderTitleScreen();
			break;
		case GameState::Countdown:
			countdown();
			break;
		case GameState::Playing:
			handleInput();
			update();
			renderPlaying();
			break;
		case GameState::GameOver:
			handleGameOverInput();
			renderGameOver();
			break;
		case GameState::Leaderboard:
			loadLeaderboard();
			handleLeaderboardInput();
			renderLeaderboard();
			break;
		}
	}
}

std::vector<sf::Texture> Game::getExplosionTextures()
{
	return explosionTextures;
}

sf::RenderWindow* Game::getWindow()
{
	return &window;
}

std::vector<sf::Texture> Game::loadBackgroundTextures(int path_to_background)
{
	//fill choosenBackgroundTextures
	choosenBackgroundTextures.reserve(numberOfFilesInDirectory[path_to_background]);
	for (int i = 0; i < numberOfFilesInDirectory[path_to_background]; i++)
	{
		sf::Texture texture;
		std::string path = pathToBackgrounds[path_to_background] + "/layer_" + std::to_string(numberOfFilesInDirectory[path_to_background]-i) + ".png";
		texture.loadFromFile(path);
		choosenBackgroundTextures.push_back(texture);
	}
	return choosenBackgroundTextures;
}
