#include "Player.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

Player::Player() : velocity(0.1f) {
    
}

Player::Player(sf::Texture& texture, float startX, float startY) : velocity(0.1f) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(startX, startY);
}

void Player::move(sf::Vector2f direction) {
    sprite.move(direction * velocity);
}

void Player::update() {
    
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::setRotation(float angle)
{
    sprite.setRotation(angle);
}

sf::FloatRect Player::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void Player::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}
