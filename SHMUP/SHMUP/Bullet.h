#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Enemy.h"

class Bullet {
public:
    Bullet(sf::Texture& texture, float startX, float startY, bool isEnemy);
    Bullet(const sf::Texture* texture, float x, float y, bool cond);
    void update();
    void draw(sf::RenderWindow& window);
    bool isActive() const;
    void setActive(bool cond);
    sf::FloatRect getGlobalBounds();
    const sf::Texture* getTexture();

private:
    sf::Sprite sprite;
    bool active;
    float velocity;
};
