#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "entities.h"
class Renderer;
class InputManager;
class ModelStore;

//Generel systems
void movementSystem(entt::registry& registry, const float deltaTime);
void renderingSystem(entt::registry& registry, Renderer& renderer);
void cleanUpSystem(entt::registry& registry);

//Player systems
void playerInputSystem(entt::registry& registry, const InputManager& inputManager, ModelStore& modelStore, const float deltaTime);
void restorePlayerHealthSystem(entt::registry& registry);

//Enemy & player systems
void receivingDamageSystem(entt::registry& registry, const float deltaTime);

//Enemy systems
void enemyShootingSystem(entt::registry& registry, ModelStore& modelStore, const float deltaTime);

//Helping functions
float getRandomDelay(float min, float max);

#endif // !SYSTEMS_H
