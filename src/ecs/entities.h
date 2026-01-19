#pragma once

#ifndef ENTITIES_H
#define ENTITIES_H

#include "components.h"
class Model;
class ModelStore;

/**
 * @brief Types of enemies that can be created in the game.
 */
enum class EnemyType {
    Basic, ///< Standard enemy with balanced stats
    Slim,  ///< Fast enemy with lower health
    Bulky  ///< Slow enemy with higher health
};

/**
 * @brief Creates a player entity and assigns all required player components.
 *
 * The player is initialized with transform, health, rendering, animation,
 * timing, statistics and player tag components.
 *
 * @param registry Reference to the EnTT registry.
 * @param object Shared pointer to the player model.
 * @param position Initial world position of the player.
 * @return Created player entity.
 */
entt::entity createPlayer(entt::registry& registry, std::shared_ptr<Model> object, const glm::vec3& position);

/**
 * @brief Creates an enemy entity based on the specified enemy type.
 *
 * Enemy properties such as model, health and movement speed depend
 * on the provided EnemyType.
 *
 * @param registry Reference to the EnTT registry.
 * @param enemyType Type of enemy to create.
 * @param modelStore Model storage used to load enemy models.
 * @param lane Lane in which the enemy should be spawned.
 * @return Created enemy entity.
 */
entt::entity createEntity(entt::registry& registry, EnemyType enemyType, ModelStore& modelStore, Lane::Lane& lane);

/**
 * @brief Creates a bullet entity fired by a player or an enemy.
 *
 * The bullet damage and tag depend on the source entity type.
 *
 * @param registry Reference to the EnTT registry.
 * @param fromWho Entity type that fired the bullet.
 * @param object Shared pointer to the bullet model.
 * @param position Initial bullet position.
 * @param rotation Initial bullet rotation.
 * @param velocity Bullet movement velocity.
 * @return Created bullet entity.
 */
entt::entity createBullet(entt::registry& registry, const EntityTypes fromWho, std::shared_ptr<Model> object, glm::vec3& position, const glm::vec3& rotation, const glm::vec3& velocity);

#endif // !ENTITIES_H
