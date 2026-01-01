#pragma once

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "../renderer/model.h"


struct Transform {
    glm::vec3 position{};
    glm::mat3 rotate{};
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
};

struct Lifetime {
    float timeRemaining;
};

struct ShouldDestroy {
    bool shuld{ false };
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