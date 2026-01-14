#pragma once

#ifndef ENTITIES_H
#define ENTITIES_H

#include "components.h"
class Model;
class ModelStore;

enum class EnemyType {
	Basic,
	Slim,
	Bulky
};

entt::entity createPlayer(entt::registry& registry, std::shared_ptr<Model> object, const glm::vec3& position);
entt::entity createEntity(entt::registry& registry, EnemyType enemyType, ModelStore& modelStore, Lane::Lane& lane);
entt::entity createBullet(entt::registry& registry, const EntityTypes fromWho, std::shared_ptr<Model> object, glm::vec3& position, const glm::vec3& velocity);

#endif // !ENTITIES_H
