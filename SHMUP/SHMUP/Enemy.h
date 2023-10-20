#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Enemy {
public:
    Enemy(sf::Texture& texture, float startX, float startY, bool canShoot);
    void update();
    void draw(sf::RenderWindow& window);
    bool isActive() const;
    bool canShoot() const;
    sf::FloatRect getGlobalBounds();
    void setActive(bool cond);

private:
    sf::Sprite sprite;
    bool active;
    float velocity;
    bool canShootFlag;
    float shootTimer;
};

