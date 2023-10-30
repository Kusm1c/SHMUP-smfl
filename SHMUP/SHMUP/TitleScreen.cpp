#include <SFML/Window/Mouse.hpp>

#include "Game.h"

void Game::handleTitleScreenInput() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    bool startButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                              mousePosition.x >= startButtonPosition.x &&
                              mousePosition.x <= startButtonPosition.x + startButtonSize.x &&
                              mousePosition.y >= startButtonPosition.y &&
                              mousePosition.y <= startButtonPosition.y + startButtonSize.y;

    bool leaderboardButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                                    mousePosition.x >= leaderboardButtonPosition.x &&
                                    mousePosition.x <= leaderboardButtonPosition.x + leaderboardButtonSize.x &&
                                    mousePosition.y >= leaderboardButtonPosition.y &&
                                    mousePosition.y <= leaderboardButtonPosition.y + leaderboardButtonSize.y;

    bool quitButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                            mousePosition.x >= quitButtonPosition.x &&
                            mousePosition.x <= quitButtonPosition.x + quitButtonSize.x &&
                            mousePosition.y >= quitButtonPosition.y &&
                            mousePosition.y <= quitButtonPosition.y + quitButtonSize.y;

    if (startButtonPressed) {
        stateManager.changeState(GameState::Countdown);
    } else if (leaderboardButtonPressed) {
        stateManager.changeState(GameState::Leaderboard);
    } else if (quitButtonPressed) {
        window.close();
    }
}
void Game::renderTitleScreen() {
    
    window.clear();

    sf::Sprite backgroundSprite(backgroundTexture);
    window.draw(backgroundSprite);

    
    
    font.loadFromFile("Font/Raleway-Medium.ttf"); 
    sf::Text titleText("Le shmup en cpp là", font, 48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(200, 50); 
    window.draw(titleText);

    
    startButtonPosition = sf::Vector2f(300, 200); 
    startButtonSize = sf::Vector2f(200, 50); 
    sf::RectangleShape startButton(sf::Vector2f(200, 50)); 
    startButton.setPosition(300, 200); 
    startButton.setFillColor(sf::Color::Green); 
    window.draw(startButton);

    
    leaderboardButtonPosition = sf::Vector2f(300, 300); 
    leaderboardButtonSize = sf::Vector2f(200, 50); 
    sf::RectangleShape leaderboardButton(sf::Vector2f(200, 50)); 
    leaderboardButton.setPosition(300, 300); 
    leaderboardButton.setFillColor(sf::Color::Blue); 
    window.draw(leaderboardButton);

    
    quitButtonPosition = sf::Vector2f(300, 400); 
    quitButtonSize = sf::Vector2f(200, 50); 
    sf::RectangleShape quitButton(sf::Vector2f(200, 50)); 
    quitButton.setPosition(300, 400); 
    quitButton.setFillColor(sf::Color::Red); 
    window.draw(quitButton);

    
    sf::Text startButtonText("Start", font, 24);
    startButtonText.setFillColor(sf::Color::Black);
    startButtonText.setPosition(350, 210); 
    window.draw(startButtonText);

    sf::Text leaderboardButtonText("Leaderboard", font, 24);
    leaderboardButtonText.setFillColor(sf::Color::Black);
    leaderboardButtonText.setPosition(320, 310); 
    window.draw(leaderboardButtonText);

    sf::Text quitButtonText("Quit", font, 24);
    quitButtonText.setFillColor(sf::Color::Black);
    quitButtonText.setPosition(350, 410); 
    window.draw(quitButtonText);

    window.display();
}
