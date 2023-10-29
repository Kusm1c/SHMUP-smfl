#include "Enemy.h"
#include "Bullet.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

Enemy::Enemy(sf::Texture& texture, float startX, float startY, bool canShoot) : active(true), velocity(0.1f), canShootFlag(canShoot), shootTimer(0) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(startX, startY);
}

void Enemy::update() {
    if (active) {
        
        sprite.move(-velocity, 0);

        
        if (canShootFlag) {
            shootTimer++;
            //spawn bullet with negative velocity and isEnemy flag
            if (shootTimer > 100) {
                shootTimer = 0;
                auto* bullet = new Bullet(sprite.getTexture(), sprite.getPosition().x, sprite.getPosition().y, true);
            }
        }
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

bool Enemy::isActive() const {
    return active;
}

bool Enemy::canShoot() const {
    return canShootFlag;
}

sf::FloatRect Enemy::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void Enemy::setActive(bool cond)
{
    active = cond;
}
