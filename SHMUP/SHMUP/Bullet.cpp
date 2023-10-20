#include "Bullet.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

Bullet::Bullet(sf::Texture& texture, float startX, float startY, bool isEnemy) : active(true), velocity(0.1f) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(startX, startY);

    if (isEnemy) {
        // Set specific properties for enemy bullets if needed.
    }
}

Bullet::Bullet(const sf::Texture* texture, float x, float y, bool cond)
{
    Bullet(*const_cast<sf::Texture*>(texture), x, y, cond);
}

void Bullet::update() {
    if (active) {
        // Move the bullet.
        sprite.move(velocity, 0);
        // Additional update logic, such as checking boundaries or handling collisions.
        if (sprite.getPosition().x > 800) {
            active = false;
        }
        if (sprite.getPosition().x < 0) {
            active = false;
        }
    }
}

void Bullet::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

bool Bullet::isActive() const {
    return active;
}

void Bullet::setActive(bool cond)
{
    active = cond;
}

sf::FloatRect Bullet::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

const sf::Texture* Bullet::getTexture()
{
    return sprite.getTexture();
}
