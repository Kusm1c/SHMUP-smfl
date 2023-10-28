#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

class Game {
public:
    Game();
    void run();

private:
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
    void handleCollisions();

    int frameCounter = 0;

    void handleInput();
    void update();
    void render();
    void spawnEnemy();
    static void updateBackground(sf::Sprite* sprite, sf::Sprite* sprite2, float sizeHeight);
    void updateBackground();
};
