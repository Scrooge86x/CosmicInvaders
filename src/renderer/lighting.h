#pragma once

#ifndef LIGHTING_H
#define LIGHTING_H

#include <glm/glm.hpp>

struct Lighting {
    glm::vec3 ambient{ 0.3f };
    glm::vec3 sunPosition{};
    glm::vec3 sunColor{ 0.5f };
};

#endif // LIGHTING_H
