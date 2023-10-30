﻿#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include "Game.h"

void Game::handleInput()
{
	sf::Vector2f movement(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		movement.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		movement.x -= 1;
		//player.setRotation(270);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x += 1;
		//player.setRotation(90);
	}
	player.setRotation(90);

	player.move(movement);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (bulletCooldownClock.getElapsedTime().asMilliseconds() >= 300)
		{
			for (auto& bullet : bullets)
			{
				if (!bullet.isActive())
				{
					bullet = Bullet(bulletTexture, player.getGlobalBounds().left + player.getGlobalBounds().width,
					                player.getGlobalBounds().top + player.getGlobalBounds().height / 2, false);
					bulletCooldownClock.restart();

					break;
				}
			}
		}
	}
}

void Game::update()
{
	player.update();
	for (auto& bullet : bullets)
	{
		bullet.update();
	}
	for (auto& enemy : enemies)
	{
		enemy.update();
	}

	handleCollisions();
	updateBackground();
	spawnEnemy();
}

void Game::handleCollisions()
{
	for (auto& bullet : bullets)
	{
		if (bullet.isActive())
		{
			for (auto& enemy : enemies)
			{
				if (enemy.isActive() && bullet.getGlobalBounds().intersects(enemy.getGlobalBounds()))
				{
					if(enemy.canBeDestroyed())
					{
						enemy.setActive(false);
						updateScore();
					}
					bullet.setActive(false);
					
					
				}
			}
		}
	}

	for (auto& enemy : enemies)
	{
		if (enemy.isActive() && player.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		{
			saveToLeaderboard();
			stateManager.changeState(GameState::GameOver);
		}
	}
}

void Game::renderPlaying()
{
	window.clear();
	drawBackground();
	player.draw(window);
	for (auto& bullet : bullets)
	{
		bullet.draw(window);
	}
	for (auto& enemy : enemies)
	{
		enemy.draw(window);
	}
	drawCurrentScore();
	window.display();
}

void Game::updateBackground()
{
	for (int i = 0; i < choosenBackgroundSprites.size(); i++)
	{
		if (choosenBackgroundSprites[i].getPosition().x < -1280)
		{
			choosenBackgroundSprites[i].setPosition(
				choosenBackgroundSprites[i].getPosition().x + 1280 * choosenBackgroundSprites.size(), 0);
		}
		choosenBackgroundSprites[i].move(-0.01f * i, 0);
	}
	for (auto& choosenBackgroundSprite : choosenBackgroundSprites)
	{
		if (choosenBackgroundSprite.getPosition().x < -1280)
		{
			choosenBackgroundSprite.setPosition(
				choosenBackgroundSprite.getPosition().x + 1280 * choosenBackgroundSprites.size(), 0);
		}
	}
}

void Game::drawBackground()
{
	for (auto& backgroundSprite : choosenBackgroundSprites)
	{
		window.draw(backgroundSprite);
	}
}

void Game::drawCurrentScore()
{
	sf::Text scoreText("Score: " + std::to_string(currentScore), font, 24);
	window.draw(scoreText);
}

void Game::spawnEnemy()
{
	if (frameCounter % 1000 == 0)
	{
		for (auto& enemy : enemies)
		{
			if (!enemy.isActive())
			{
				if (rand() % 2 == 0)
				{
					enemy = Enemy(enemyTexture, window.getSize().x, rand() % window.getSize().y, true);
					enemy.setVelocity(rand() % 10 / 100.0f + 0.1f);
				}
				else
				{
					
					enemy = Enemy(asteroidTexture, window.getSize().x, rand() % window.getSize().y, false);
					enemy.setVelocity(0.01f);
				}
				break;
			}
		}
		//enemies.emplace_back(enemyTexture, 800, rand() % 600, true);
	}
	frameCounter++;
}

void Game::updateScore()
{
	currentScore++;
}
