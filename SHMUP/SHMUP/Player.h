#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Player {
public:
    Player();
    Player(sf::Texture& texture, float startX, float startY);
    void move(sf::Vector2f direction);
    void update();
    void draw(sf::RenderWindow& window);
    void setRotation(float angle);
    sf::FloatRect getGlobalBounds();

private:
    sf::Sprite sprite;
    float velocity;
};
