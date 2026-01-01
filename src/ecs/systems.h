#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
class Renderer;
class InputManager;

//Generel systems
void movementSystem(entt::registry& registry);
void renderingSystem(entt::registry& registry, Renderer& renderer, glm::mat4& model);
void cleanUpSystem(entt::registry& registry);

//Player systems
void playerInputSystem(entt::registry& registry, const InputManager& inputManager);
void shootingSystem(entt::registry& registry);

//Enemy systems
void beingShotSystem(entt::registry& registry);

#endif // !SYSTEMS_H
