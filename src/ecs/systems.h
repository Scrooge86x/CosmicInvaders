#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
class Renderer;

//Generel systems
void movementSystem(entt::registry& registry);
void renderingSystem(entt::registry& registry, Renderer& renderer, glm::mat4& model);
void cleanUpSystem(entt::registry& registry);

//Player systems
void shootingSystem(entt::registry& registry);

//Enemy systems
void beingShotSystem(entt::registry& registry);

#endif // !SYSTEMS_H
