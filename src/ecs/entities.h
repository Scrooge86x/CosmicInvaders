#pragma once

#ifndef ENTITIES_H
#define ENTITIES_H

#include "components.h"
class Model;

entt::entity createPlayer(entt::registry& registry, std::shared_ptr<Model> object);
entt::entity createEntity(entt::registry& registry, std::shared_ptr<Model> object, glm::vec3& position, std::string& type);
entt::entity createBullet(entt::registry& registry, const EntityTypes fromWho, std::shared_ptr<Model> object, glm::vec3& position, glm::vec3 direction);

#endif // !ENTITIES_H
