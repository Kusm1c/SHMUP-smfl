#pragma once

#include <glm/glm.hpp>
#include "Terrain.h"

class Player {
public:
    glm::vec3 position;
    float size;

    Player(glm::vec3 startPos, float playerSize);

    bool checkCollision(const Terrain& terrain) const;
};
