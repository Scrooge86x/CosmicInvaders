#pragma once

#ifndef QUERIES_H
#define QUERIES_H

#include "components.h"

/**
 * @brief Checks whether the player entity is alive.
 *
 * The function assumes that exactly one entity with PlayerTag exists
 * in the registry.
 *
 * @param registry Constant reference to the ECS registry.
 * @return True if the player's current health is greater than zero,
 *         false otherwise.
 */
bool isPlayerAlive(const entt::registry& registry);

/**
 * @brief Checks if at least one enemy entity exists.
 *
 * @param registry Constant reference to the ECS registry.
 * @return True if the registry contains any entity with EnemyTag,
 *         false otherwise.
 */
bool enemyExists(const entt::registry& registry);

/**
 * @brief Retrieves the player's Health component.
 *
 * The function assumes that exactly one entity with PlayerTag exists
 * in the registry.
 *
 * @param registry Constant reference to the ECS registry.
 * @return A copy of the player's Health component.
 */
Health getPlayerHealth(const entt::registry& registry);

/**
 * @brief Retrieves the player's Stats component.
 *
 * The function assumes that exactly one entity with PlayerTag exists
 * in the registry.
 *
 * @param registry Constant reference to the ECS registry.
 * @return A copy of the player's Stats component.
 */
Stats getPlayerStats(const entt::registry& registry);

#endif // !QUERIES_H