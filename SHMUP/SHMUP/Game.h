#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Bullet.h"
#include "Enemy.h"
#include "GameState.h"
#include "Player.h"

class Game {
public:
    Game();
    void run();

private:
    // Member variables

    // Initialization functions
    void handleInput();
    void handleTitleScreenInput();
    void handleLeaderboardInput();
    void handleGameOverInput();

    // Game state handling functions
    void countdown();
    void update();
    void handleCollisions();
    void spawnEnemy();
    void updateBackground();
    void resetGame();

    // Rendering functions
    void renderPlaying();
    void renderTitleScreen();
    void renderLeaderboard();
    void renderGameOver();

    // Score and leaderboard functions
    void updateScore();
    void saveToLeaderboard();
    void loadLeaderboard();
    void showLeaderboard();

    // Member variables
    GameStateManager stateManager;
    sf::RenderWindow window;
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    sf::Texture playerTexture;
    sf::Texture bulletTexture;
    sf::Texture enemyTexture;
    sf::Texture backgroundTexture;
    std::vector<sf::Sprite> backgroundSprites;
    sf::Clock bulletCooldownClock;
    sf::Font font;
    sf::Text countdownText;
    sf::Text scoreText;
    int currentScore;
    std::vector<int> leaderboardScores;
    
    sf::Vector2f startButtonPosition;
    sf::Vector2f startButtonSize;
    sf::Vector2f leaderboardButtonPosition;
    sf::Vector2f leaderboardButtonSize;
    sf::Vector2f quitButtonPosition;
    sf::Vector2f quitButtonSize;
    sf::Vector2f retryButtonPosition;
    sf::Vector2f retryButtonSize;
    sf::Vector2f giveUpButtonPosition;
    sf::Vector2f giveUpButtonSize;
    sf::Vector2f backButtonPosition;
    sf::Vector2f backButtonSize;
    GameState currentState;
    int frameCounter = 0;

    // Static utility function
    static void updateBackground(sf::Sprite* sprite, sf::Sprite* sprite2, float sizeHeight);
};