#pragma once

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "../renderer/model.h"

class Lane {
public:
    enum class lane {
        Left,
        Middle,
        Right
    };

    enum class laneDirection {
        Left,
        Right
    };

    static lane changeLane(lane current, laneDirection direction) {
        bool moveRight = (direction == laneDirection::Right);

        switch (current) {
        case lane::Left:
            return moveRight ? lane::Middle : current;
        case lane::Middle:
            return moveRight ? lane::Right : lane::Left;
        case lane::Right:
            return moveRight ? current : lane::Middle;
        default:
            return current;
        }
    }

    static float getLaneXPosition(lane current) {
        switch (current) {
        case lane::Left:
            return -3.75f;
        case lane::Middle:
            return 0.f;
        case lane::Right:
            return 3.75f;
        default:
            return 0.f;
        }
    }
};

enum class EntityTypes {
    Player,
    Enemy
};

struct Transform {
    glm::vec3 position{};
    glm::vec3 rotation{};
};

struct Health {
    int max;
    int current;
};

struct Damage {
    int current{ 1 };
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

struct Animation {
    Lane::lane currentLane{ Lane::lane::Middle };
    Lane::lane targetLane{ Lane::lane::Middle };
    float animationTime{};
};

struct Stats {
    int lostHealth{};
    double firedBullets{};
    float damageDealt{};
};

struct TimeDelay {
    float time{};
    float time2{};
};

struct FromWho {
    EntityTypes fromWho;
};

struct PlayerTag {};
struct EnemyTag {};
struct EnemyBulletTag {};
struct PlayerBulletTag {};

#endif // !COMPONENTS_H