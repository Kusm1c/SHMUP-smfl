#include <fstream>
#include <SFML/Window/Mouse.hpp>

#include "Game.h"

void Game::saveToLeaderboard() {
    std::ofstream file("leaderboard.txt", std::ios::app); 
    if (file.is_open()) {
        file << currentScore << "\n"; 
        file.close(); 
    }
}

void Game::loadLeaderboard() {
    std::ifstream file("leaderboard.txt");
    leaderboardScores.clear(); 

    if (file.is_open()) {
        int score;
        while (file >> score) {
            
            auto it = std::lower_bound(leaderboardScores.begin(), leaderboardScores.end(), score, std::greater<int>());
            leaderboardScores.insert(it, score); 
        }
        file.close(); 
    }
}

void Game::handleLeaderboardInput() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        bool backButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                            mousePosition.x >= backButtonPosition.x &&
                            mousePosition.x <= backButtonPosition.x + backButtonSize.x &&
                            mousePosition.y >= backButtonPosition.y &&
                            mousePosition.y <= backButtonPosition.y + backButtonSize.y;

    if (backButtonPressed) {
        stateManager.changeState(GameState::TitleScreen);
    }
}

void Game::renderLeaderboard() {
    sf::Font font;
    font.loadFromFile("Font/Raleway-Medium.ttf"); 

    
    sf::Text leaderboardHeading("Leaderboard", font, 48);
    leaderboardHeading.setFillColor(sf::Color::White);
    leaderboardHeading.setPosition(200, 25); 

    
    std::vector<sf::Text> leaderboardEntries;
    for (size_t i = 0; i < 10; ++i) {
        sf::Text entryText(std::to_string(i + 1) + ". " + std::to_string(leaderboardScores[i]), font, 24);
        entryText.setFillColor(sf::Color::White);
        entryText.setPosition(250, 100 + i * 40); 
        leaderboardEntries.push_back(entryText);
    }

    
    window.clear();

    
    window.draw(leaderboardHeading);

    
    for (const auto& entry : leaderboardEntries) {
        window.draw(entry);
    }

    
    backButtonPosition = sf::Vector2f(50, 450); 
    backButtonSize = sf::Vector2f(150, 50); 
    sf::RectangleShape backButton(sf::Vector2f(150, 50)); 
    backButton.setPosition(backButtonPosition);
    backButton.setFillColor(sf::Color::Blue); 

    
    sf::Text backButtonText("Back to Title", font, 24);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(60, 460); 

    
    window.draw(backButton);
    window.draw(backButtonText);

    
    window.display();
}