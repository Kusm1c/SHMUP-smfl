#include <iostream>
#include <SFML/Window/Mouse.hpp>

#include "Game.h"

void Game::resetGame() {
    player.setPosition(400, 300); 

    
    bullets.clear(); 
    bullets.reserve(100); 
    for (int i = 0; i < 100; i++) {
        bullets.emplace_back(bulletTexture, -800, -800, false);
    }

    enemies.clear(); 
    currentScore = 0; 
}

void Game::handleGameOverInput() {
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

    if (retryButtonPressed) {
        
        resetGame();
        stateManager.changeState(GameState::Countdown);
        std::cout << "Retry button pressed" << std::endl;
    } else if (giveUpButtonPressed) {
        
        stateManager.changeState(GameState::TitleScreen);
        std::cout << "Give up button pressed" << std::endl;
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

    
    retryButtonPosition = sf::Vector2f(200, 300); 
    retryButtonSize = sf::Vector2f(150, 50); 
    sf::RectangleShape retryButton(retryButtonSize); 
    retryButton.setPosition(retryButtonPosition); 
    retryButton.setFillColor(sf::Color::Green); 

    
    giveUpButtonPosition = sf::Vector2f(450, 300); 
    giveUpButtonSize = sf::Vector2f(150, 50); 
    sf::RectangleShape giveUpButton(giveUpButtonSize); 
    giveUpButton.setPosition(giveUpButtonPosition); 
    giveUpButton.setFillColor(sf::Color::Red); 
    
    
    sf::Text retryButtonText("Retry?", font, 24);
    retryButtonText.setFillColor(sf::Color::Black);
    retryButtonText.setPosition(240, 310); 

    sf::Text giveUpButtonText("Give up", font, 24);
    giveUpButtonText.setFillColor(sf::Color::Black);
    giveUpButtonText.setPosition(480, 310); 

    
    window.draw(gameOverText);
    window.draw(retryButton);
    window.draw(giveUpButton);
    window.draw(retryButtonText);
    window.draw(giveUpButtonText);

    
    window.display();
}