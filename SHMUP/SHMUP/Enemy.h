#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Enemy {
public:
    Enemy(sf::Texture& texture, float startX, float startY, bool isDestructible);
    void update();
    void draw(sf::RenderWindow& window);
    bool isActive() const;
    bool canBeDestroyed() const;
    sf::FloatRect getGlobalBounds();
    void setActive(bool cond);
    void setVelocity(float velocity);

private:
    sf::Sprite sprite;
    bool active;
    float velocity;
    bool isDestructibleFlag;
    float shootTimer;
    float randomAmplitude;
    float randomFrequency;
};

