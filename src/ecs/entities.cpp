#include "entities.h"

entt::entity createPlayer(entt::registry& registry, Model& object) {
	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, glm::vec3(0.0f, 0.0f, 0.0f));
	registry.emplace<Velocity>(entity);
	registry.emplace<Health>(entity, 100.0f, 100.0f);
	registry.emplace<Render>(entity, object);
	registry.emplace<PlayerTag>(entity);

	return entity;
}

entt::entity createEntity(entt::registry& registry, Model& object, glm::vec3& position, std::string& type) {
	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, position);
	registry.emplace<Velocity>(entity);
	registry.emplace<Health>(entity, 100.0f, 100.0f);
	registry.emplace<Render>(entity, object);
	registry.emplace<EnemyTag>(entity, type);
	registry.emplace<ShouldDestroy>(entity);

	return entity;
}

entt::entity createBullet(entt::registry& registry, Model& object, glm::vec3& position) {
	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, position);
	registry.emplace<Velocity>(entity);
	registry.emplace<Render>(entity, object);
	registry.emplace<BulletTag>(entity);

	return entity;
}