#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>

int currentScore;
std::vector<int> leaderboardScores;

Game::Game() : window(sf::VideoMode(800, 500), "SFML Game") {
    
    playerTexture.loadFromFile("img/PlayerShip.png");
    bulletTexture.loadFromFile("img/Bullet.png");
    enemyTexture.loadFromFile("img/cruiser.png");
    backgroundTexture.loadFromFile("img/BackGround.png");

    
    player = Player(playerTexture, 400, 300);

    
    bullets.reserve(100);
    enemies.reserve(100);

    
    for (int i = 0; i < 100; i++) {
        bullets.emplace_back(bulletTexture, -800, -800, false);
    }

    
    backgroundSprites.resize(2);
    for (int i = 0; i < 2; ++i) {
        backgroundSprites[i].setTexture(backgroundTexture);
        backgroundSprites[i].setPosition(800 * i, 0);
    }

    
    std::srand(std::time(0));
}

void Game::run() {
     
    stateManager.changeState(GameState::TitleScreen); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        
        switch (stateManager.getState()) {
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