#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
#include "../renderer/shader.h"
//#include "../renderer/immediate-renderer.h"

//Generel systems
void movementSystem(entt::registry& registry);
void renderingSystem(entt::registry& registry, Shader& shader, glm::mat4& model);
void cleanUpSystem(entt::registry& registry);

//Player systems
void shootingSystem(entt::registry& registry);

//Enemy systems
void beingShotSystem(entt::registry& registry);

#endif // !SYSTEMS_H
