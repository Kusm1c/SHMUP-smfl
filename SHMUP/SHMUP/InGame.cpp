#include <SFML/Window/Keyboard.hpp>

#include "Game.h"
void Game::handleInput() {
    
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
                    bulletCooldownClock.restart(); 
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

void Game::handleCollisions() {
    for (auto& bullet : bullets) {
        if (bullet.isActive()) {
            for (auto& enemy : enemies) {
                if (enemy.isActive() && bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                    bullet.setActive(false);
                    enemy.setActive(false);
                    updateScore(); 
                }
            }
        }
    }

    for (auto& enemy : enemies) {
        if (enemy.isActive() && player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            saveToLeaderboard();
            stateManager.changeState(GameState::GameOver);
        }
    }
}

void Game::renderPlaying() {
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

void Game::updateScore() {
    currentScore++;
}