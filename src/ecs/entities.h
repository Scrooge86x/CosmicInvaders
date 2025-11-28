#pragma once

#ifndef ENTITIES_H
#define ENTITIES_H

#include "components.h"

entt::entity createPlayer(entt::registry& registry, Model& object);
entt::entity createEntity(entt::registry& registry, Model& object, glm::vec3& position, std::string& type);
entt::entity createBullet(entt::registry& registry, Model& object, glm::vec3& position);

#endif // !ENTITIES_H
