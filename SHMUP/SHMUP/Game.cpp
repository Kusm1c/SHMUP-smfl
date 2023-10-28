#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

Game::Game() : window(sf::VideoMode(800, 500), "SFML Game") {
    // Load textures for player, bullet, and enemy.
    playerTexture.loadFromFile("img/PlayerShip.png");
    bulletTexture.loadFromFile("img/Bullet.png");
    enemyTexture.loadFromFile("img/cruiser.png");
    backgroundTexture.loadFromFile("img/BackGround.png");

    // Initialize player.
    player = Player(playerTexture, 400, 300);

    // Initialize Bullet and Enemy vectors.
    bullets.reserve(100);
    enemies.reserve(100);

    // Initialize the pool of bullets.
    for (int i = 0; i < 100; i++) {
        bullets.emplace_back(bulletTexture, -800, -800, false);
    }

    // Initialize background sprites.
    backgroundSprites.resize(2);
    for (int i = 0; i < 2; ++i) {s
        backgroundSprites[i].setTexture(backgroundTexture);
        backgroundSprites[i].setPosition(800 * i, 0);
    }

    // Seed for random number generation.
    std::srand(std::time(0));
}

void Game::handleCollisions() {
    for (auto& bullet : bullets) {
        if (bullet.isActive()) {
            for (auto& enemy : enemies) {
                if (enemy.isActive() && bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                    bullet.setActive(false);
                    enemy.setActive(false);
                }
            }
        }
    }

    for (auto& enemy : enemies) {
        if (enemy.isActive() && player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            window.close();
        }
    }
}

void Game::handleInput() {
    // Handle user input, update player position, and fire bullets.
    sf::Vector2f movement(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        movement.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        movement.x -= 1;
        player.setRotation(270);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += 1;
        player.setRotation(90);
    }

    player.move(movement);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (bulletCooldownClock.getElapsedTime().asMilliseconds() >= 500) {
            for (auto& bullet : bullets) {
                if (!bullet.isActive()) {
                    bullet = Bullet(bulletTexture, player.getGlobalBounds().left + player.getGlobalBounds().width, player.getGlobalBounds().top + player.getGlobalBounds().height / 2, false);
                    bulletCooldownClock.restart(); // Reset the cooldown timer
                    break;
                }
            }
        }
    }
}

void Game::update() {
    player.update();
    for (auto& bullet : bullets) {
        bullet.update();
    }
    for (auto& enemy : enemies) {
        enemy.update();
    }
    handleCollisions();
    updateBackground();
    spawnEnemy();
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprites[0]);
    window.draw(backgroundSprites[1]);
    player.draw(window);
    for (auto& bullet : bullets) {
        bullet.draw(window);
    }
    for (auto& enemy : enemies) {
        enemy.draw(window);
    }
    window.display();
}

void Game::updateBackground() {
    for (auto& sprite : backgroundSprites) {
        sprite.move(-0.01, 0);
        if (sprite.getPosition().x < -800) {
            sprite.setPosition(800, 0);
        }
    }
}

void Game::spawnEnemy() {
    if (frameCounter % 1000 == 0) {
        enemies.emplace_back(enemyTexture, 800, rand() % 600, true);
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
        update();
        render();
    }
}

