#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


Game::Game() : window(sf::VideoMode(800, 500), "SFML Game") {
    // Load textures for player, bullet, and enemy.
    playerTexture.loadFromFile("img/PlayerShip.png");
    bulletTexture.loadFromFile("img/Bullet.png");
    enemyTexture.loadFromFile("img/cruiser.png");

    // Initialize player.
    player = Player(playerTexture, 400, 300);

    // Initialize Bullet and Enemy vectors.
    bullets = std::vector<Bullet>();
    enemies = std::vector<Enemy>();

    // Initialize the pool of bullets.
    for (int i = 0; i < 100; i++) {
        bullets.push_back(Bullet(bulletTexture, 0, 0, false));
    }

    //make 2 backgrounds
    backgroundTexture.loadFromFile("img/BackGround.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);
    backgroundSprite2.setTexture(backgroundTexture);
    backgroundSprite2.setPosition(800, 0);
}

void Game::handleCollisions()
{
    // Handle collisions between player, bullets, and enemies.
    // If a collision occurs, set the active flag to false. If the player is hit, end the game.
    for (auto& bullet : bullets) {
        if (bullet.isActive()) {
            for (auto& enemy : enemies) {
                if (enemy.isActive()) {
                    if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                        bullet.setActive(false);
                        enemy.setActive(false);
                    }
                }
            }
        }
    }
    for (auto& enemy : enemies) {
        if (enemy.isActive()) {
            if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                window.close();
            }
        }
    }
}

void Game::handleInput() {
    // Handle user input, update player position, and fire bullets.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        player.move(sf::Vector2f(0, -1));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        player.move(sf::Vector2f(-1, 0));
        player.setRotation(270);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.move(sf::Vector2f(0, 1));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.move(sf::Vector2f(1, 0));
        player.setRotation(90);
    }

    // when space is pressed, fire only one bullet per press
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (frameCounter % 500 == 0) {
            for (auto& bullet : bullets) {
                if (!bullet.isActive()) {
                    bullet = Bullet(bulletTexture, player.getGlobalBounds().left + player.getGlobalBounds().width, player.getGlobalBounds().top + player.getGlobalBounds().height / 2, false);
                    break;
                }
            }
        }
    }
}

void Game::update() {
    // Update player, bullets, enemies, handle collisions, etc.
    // Spawn new enemies based on game logic.
    player.update();
    for (auto& bullet : bullets) {
        bullet.update();
    }
    for (auto& enemy : enemies) {
        enemy.update();
    }
    updateBackground(&backgroundSprite, &backgroundSprite2, 1500);
    spawnEnemy();
}

void Game::render() {
    window.clear();
    update();

    window.draw(backgroundSprite);
    window.draw(backgroundSprite2);

    // Render player, bullets, enemies, background, UI, etc.
    player.draw(window);

    for (auto& bullet : bullets) {
        bullet.draw(window);
    }

    for (auto& enemy : enemies) {
        enemy.draw(window);
    }

    window.display();
}

void Game::spawnEnemy() {
    // Logic to spawn enemies based on game conditions.
    if (frameCounter % 100 == 0) {
        enemies.push_back(Enemy(enemyTexture, 800, rand() % 600, true));
    }
    frameCounter++;
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        handleInput();
        render();
    }
}

void Game::updateBackground(sf::Sprite* sprite, sf::Sprite* sprite2, float sizeHeight)
{
    sprite->move(-0.01, 0);
    sprite2->move(-0.01, 0);
    if (sprite->getPosition().x < -sizeHeight)
    {
        sprite->setPosition(sprite2->getPosition().x + sizeHeight, 0);
    }
    else if (sprite2->getPosition().x < -sizeHeight)
    {
        sprite2->setPosition(sprite->getPosition().x + sizeHeight, 0);
    }
}
