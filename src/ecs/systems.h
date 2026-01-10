#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
class Renderer;
class InputManager;
class ModelStore;

//Generel systems
void movementSystem(entt::registry& registry, const float deltaTime);
void renderingSystem(entt::registry& registry, Renderer& renderer);
void cleanUpSystem(entt::registry& registry);

//Player systems
void playerInputSystem(entt::registry& registry, const InputManager& inputManager, const ModelStore& modelStore, const float deltaTime);

//Enemy & player systems
void receivingDamageSystem(entt::registry& registry, const float deltaTime);

//Enemy systems
void enemyShootingSystem(entt::registry& registry, const InputManager& inputManager);


#endif // !SYSTEMS_H
