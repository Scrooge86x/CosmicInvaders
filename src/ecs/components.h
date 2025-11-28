#pragma once

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "../renderer/model.h"


struct Transform {
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
};

struct Health {
	float max;
	float current;
};

struct Damage {
    float current{ 1 };
};

struct Velocity {
    glm::vec3 linear{ 0.0f, 0.0f, 0.0f };
    float speed = 1.0f;
};

struct Lifetime {
    float timeRemaining;
};

struct Render {
    std::shared_ptr<Model> object;
};

struct PlayerTag {};
struct EnemyTag {
    std::string type;
};
struct BulletTag {};

#endif // !COMPONENTS_H