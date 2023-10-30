#include "Enemy.h"
#include "Game.h"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Sleep.hpp>

Enemy::Enemy(sf::Texture& texture, float startX, float startY, bool isDestructible) : active(true), velocity(0.1),isDestructibleFlag(isDestructible), shootTimer(0) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(startX, startY);
    if (isDestructible) {
        this->randomAmplitude = (rand() % 6 + 2) / 75.0f;
        this->randomFrequency = (rand() % 200 + 100);
        this->randomAmplitude *= (rand() % 10 < 4) ? 0 : 1;
    }
	else
	{
		this->randomAmplitude = 0;
		this->randomFrequency = 0;
	}
}

void Enemy::update() {
    if (active) {
        
        sprite.move(-velocity, 0);
        if (isDestructibleFlag) {
            sprite.move(0, sin(sprite.getPosition().x / randomFrequency) * randomAmplitude);
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

bool Enemy::canBeDestroyed() const {
    return isDestructibleFlag;
}

sf::FloatRect Enemy::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void Enemy::setActive(bool cond)
{
    active = cond;
}

void Enemy::setVelocity(float val)
{
	velocity = val;
}
