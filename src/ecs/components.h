#pragma once

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "../renderer/model.h"

/**
 * @brief Contains lane related enums and helper functions.
 */
namespace Lane {

    /**
     * @brief Represents possible lanes an entity can occupy.
     */
    enum class Lane {
        Left,
        Middle,
        Right
    };

    /**
     * @brief Represents direction of lane change.
     */
    enum class LaneDirection {
        Left,
        Right
    };

    /**
     * @brief Calculates a new lane based on current lane and movement direction.
     *
     * @param current Current lane
     * @param direction Direction of movement
     * @return New lane after applying the direction
     */
    inline Lane changeLane(Lane current, LaneDirection direction) {
        bool moveRight = (direction == LaneDirection::Right);

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

    /**
     * @brief Returns the world X position for a given lane.
     *
     * @param current Lane for which the X position is requested
     * @return X coordinate corresponding to the lane
     */
    inline float getLaneXPosition(Lane current) {
        switch (current) {
        case Lane::Left:
            return -3.75f;
        case Lane::Middle:
            return 0.f;
        case Lane::Right:
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

struct Render {
    std::shared_ptr<Model> object;
};

/**
 * @brief Stores lane animation state for a player.
 */
struct Animation {
    Lane::Lane currentLane{ Lane::Lane::Middle }; ///< Current lane of the entity
    Lane::Lane targetLane{ Lane::Lane::Middle };  ///< Target lane for animation
    float animationTime{};                        ///< Elapsed time of lane change animation
};

/**
 * @brief Stores gameplay statistics for a player.
 */
struct Stats {
    int lostHealth{};      ///< Amount of health lost
    double firedBullets{}; ///< Number of bullets fired
    float damageDealt{};   ///< Total damage dealt to other entities
};

/**
 * @brief Stores cooldown timers for actions.
 */
struct TimeDelay {
    float shootingDelay{};        ///< Delay between consecutive shots
    float recievingDamageDelay{}; ///< Delay after receiving damage
};

/**
 * @brief Identifies the source entity type of an bullet.
 */
struct FromWho {
    EntityTypes fromWho; ///< Type of entity that fired the bullet.
};

struct DestroyTag {};
struct PlayerTag {};
struct EnemyTag {};
struct EnemyBulletTag {};
struct PlayerBulletTag {};

#endif // !COMPONENTS_H