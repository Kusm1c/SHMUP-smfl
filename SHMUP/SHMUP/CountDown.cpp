#include "Game.h"

void Game::countdown() {
    sf::Font font;
    font.loadFromFile("Font/Raleway-Medium.ttf"); 

    int countdownValue = 3; 
    sf::Text countdownText("", font, 100);
    countdownText.setFillColor(sf::Color::White);

    sf::Clock countdownClock;
    sf::Time countdownTimer = sf::seconds(1); 

    while (countdownValue > 0) {
        window.clear();

        
        countdownText.setString(std::to_string(countdownValue));

        
        countdownText.setPosition((window.getSize().x - countdownText.getLocalBounds().width) / 2,
                                  (window.getSize().y - countdownText.getLocalBounds().height) / 2);

        
        window.draw(countdownText);

        
        window.display();

        
        while (countdownClock.getElapsedTime() < countdownTimer) {
            
        }

        
        countdownClock.restart();

        
        countdownValue--;
    }

    
    stateManager.changeState(GameState::Playing);
}