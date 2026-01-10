#pragma once

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "../renderer/model.h"

namespace Lane {
    enum class Lane {
        Left,
        Middle,
        Right
    };

    Lane changeLane(Lane current, bool moveRight) {
        switch (current) {
        case Lane::Left:
            return moveRight ? Lane::Middle : current;
        case Lane::Middle:
            return moveRight ? Lane::Right : Lane::Left;
        case Lane::Right:
            return moveRight ? current : Lane::Middle;
        default:
            return current;
        }
    }

    float getLaneXPosition(Lane current) {
        switch (current) {
        case Lane::Left:
            return -15.f;
        case Lane::Middle:
            return 0.f;
        case Lane::Right:
            return 15.f;
        }
    }
}

struct Transform {
    glm::vec3 position{};
    glm::vec3 rotate{};
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

struct ShouldDestroy {
    bool shuld{ false };
};

struct Render {
    std::shared_ptr<Model> object;
};

struct PlayerTag {
    Lane::Lane currentLane{ Lane::Lane::Middle };
    Lane::Lane targetLane{ Lane::Lane::Middle };
    float animationTime{};
    float startX = 0.0f;
    float targetX = 0.0f;

    bool canMove() const { return animationTime <= 0.0f; }
    bool canShoot() const { return animationTime <= 0.0f; }
};

struct EnemyTag {
    std::string type;
};

struct BulletTag {};

#endif // !COMPONENTS_H