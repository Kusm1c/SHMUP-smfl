#include "Player.h"
#include "Terrain.h"

Player::Player(glm::vec3 startPos, float playerSize) : position(startPos), size(playerSize) {}

bool Player::checkCollision(const Terrain& terrain) const {
    float x = position.x;
    float z = position.z;

    float height = terrain.getHeightOfGroundAtPosition(x, z);
    std::cout << height << std::endl;
    return position.y < height;
}