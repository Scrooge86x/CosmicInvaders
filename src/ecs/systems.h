#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "entities.h"
class Renderer;
class InputManager;
class ModelStore;
class AudioEngine;

//Generel systems

/**
 * @brief Updates entity positions based on their velocity.
 *
 * Iterates over all entities that have Transform and Velocity components
 * and moves them according to the elapsed frame time.
 *
 * @param registry ECS registry containing all entities.
 * @param deltaTime Time elapsed since the last frame.
 */
void movementSystem(entt::registry& registry, const float deltaTime);

/**
 * @brief Renders all drawable entities.
 *
 * Builds model matrices from Transform components and submits them
 * to the renderer using the associated Render component.
 *
 * @param registry ECS registry containing all entities.
 * @param renderer Renderer used to draw objects.
 */
void renderingSystem(entt::registry& registry, Renderer& renderer);

/**
 * @brief Destroys entities marked for removal.
 *
 * Iterates over entities with the ShouldDestroy component and
 * removes them from the registry when flagged.
 *
 * @param registry ECS registry containing all entities.
 */
void cleanUpSystem(entt::registry& registry);

//Player systems

/**
 * @brief Handles player input, movement between lanes, and shooting.
 *
 * Processes keyboard input, updates player lane animations,
 * handles shooting cooldowns, and spawns player bullets.
 *
 * @param registry ECS registry containing all entities.
 * @param inputManager Input handler providing current input state.
 * @param modelStore Storage used to load and access models.
 * @param audioEngine Audio engine for playing sound effects.
 * @param deltaTime Time elapsed since the last frame.
 */
void playerInputSystem(entt::registry& registry, const InputManager& inputManager, ModelStore& modelStore, AudioEngine& audioEngine, const float deltaTime);

/**
 * @brief Restores player health to maximum.
 *
 * Sets the player's current health value to its maximum value.
 *
 * @param registry ECS registry containing all entities.
 */
void restorePlayerHealthSystem(entt::registry& registry);

//Enemy & player systems

/**
 * @brief Processes damage received by player and enemies.
 *
 * Handles bullet collisions, enemy collisions, invincibility timing,
 * health reduction, and entity destruction.
 *
 * @param registry ECS registry containing all entities.
 * @param deltaTime Time elapsed since the last frame.
 */
void receivingDamageSystem(entt::registry& registry, const float deltaTime);

//Enemy systems

/**
 * @brief Controls enemy shooting behavior.
 *
 * Uses a randomized delay to spawn enemy bullets aimed forward.
 *
 * @param registry ECS registry containing all entities.
 * @param modelStore Storage used to load and access models.
 * @param deltaTime Time elapsed since the last frame.
 */
void enemyShootingSystem(entt::registry& registry, ModelStore& modelStore, const float deltaTime);

//Helping functions

/**
 * @brief Generates a random delay value.
 *
 * Returns a rounded floating point value within the given range.
 *
 * @param min Minimum delay value.
 * @param max Maximum delay value.
 * @return Random delay value rounded to one decimal place.
 */
float getRandomDelay(float min, float max);

#endif // !SYSTEMS_H
