#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
class Renderer;

enum Direction {
	Left = -1,
	None = 0,
	Right = 1
};

//Generel systems
void movementSystem(entt::registry& registry);
void renderingSystem(entt::registry& registry, Renderer& renderer, glm::mat4& model);
void cleanUpSystem(entt::registry& registry);

//Player systems
void playerDirectionSystem(entt::registry& registry, const Direction direction);
void shootingSystem(entt::registry& registry);

//Enemy systems
void beingShotSystem(entt::registry& registry);

#endif // !SYSTEMS_H
