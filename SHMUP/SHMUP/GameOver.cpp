#include <SFML/Window/Mouse.hpp>

#include "Game.h"

void Game::resetGame()
{
	player.setPosition(400, 300);


	bullets.clear();
	enemies.clear();
	setBulletsAndEnemiesAndBackGround();
	currentScore = 0;
}

void Game::handleGameOverInput()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);


	bool retryButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		mousePosition.x >= retryButtonPosition.x &&
		mousePosition.x <= retryButtonPosition.x + retryButtonSize.x &&
		mousePosition.y >= retryButtonPosition.y &&
		mousePosition.y <= retryButtonPosition.y + retryButtonSize.y;


	bool giveUpButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		mousePosition.x >= giveUpButtonPosition.x &&
		mousePosition.x <= giveUpButtonPosition.x + giveUpButtonSize.x &&
		mousePosition.y >= giveUpButtonPosition.y &&
		mousePosition.y <= giveUpButtonPosition.y + giveUpButtonSize.y;

	if (retryButtonPressed)
	{
		resetGame();
		stateManager.changeState(GameState::Countdown);
	}
	else if (giveUpButtonPressed)
	{
		resetGame();
		stateManager.changeState(GameState::TitleScreen);
	}
}

void Game::renderGameOver()
{
	window.clear();


	sf::Font font;
	font.loadFromFile("Font/Raleway-Medium.ttf");
	sf::Text gameOverText("Game Over", font, 48);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition((window.getSize().x - gameOverText.getLocalBounds().width) / 2, 200);


	retryButtonPosition = sf::Vector2f(window.getSize().x / 2 + 200, 300);
	retryButtonSize = sf::Vector2f(150, 50);
	sf::RectangleShape retryButton(retryButtonSize);
	retryButton.setPosition(retryButtonPosition);
	retryButton.setFillColor(sf::Color::Green);


	giveUpButtonPosition = sf::Vector2f(window.getSize().x / 2 - 200, 300);
	giveUpButtonSize = sf::Vector2f(150, 50);
	sf::RectangleShape giveUpButton(giveUpButtonSize);
	giveUpButton.setPosition(giveUpButtonPosition);
	giveUpButton.setFillColor(sf::Color::Red);


	sf::Text retryButtonText("Retry?", font, 24);
	retryButtonText.setFillColor(sf::Color::Black);
	retryButtonText.setPosition(retryButtonPosition);

	sf::Text giveUpButtonText("Give up", font, 24);
	giveUpButtonText.setFillColor(sf::Color::Black);
	giveUpButtonText.setPosition(giveUpButtonPosition);


	window.draw(gameOverText);
	window.draw(retryButton);
	window.draw(giveUpButton);
	window.draw(retryButtonText);
	window.draw(giveUpButtonText);


	window.display();
}
