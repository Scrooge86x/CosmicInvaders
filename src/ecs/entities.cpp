#include "entities.h"
#include <renderer/model.h>

entt::entity createPlayer(entt::registry& registry, std::shared_ptr<Model> object) {
	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, glm::vec3(1.0f, -2.0f, -10.0f));
	registry.emplace<Velocity>(entity);
	registry.emplace<Health>(entity, 100.0f, 100.0f);
	registry.emplace<Render>(entity, object);
	registry.emplace<Animation>(entity);
	registry.emplace<PlayerTag>(entity);

	return entity;
}

entt::entity createEntity(entt::registry& registry, std::shared_ptr<Model> object, glm::vec3& position, glm::vec3 rotate, std::string& type) {

	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, position, rotate);
	registry.emplace<Velocity>(entity);
	registry.emplace<Health>(entity, 100.0f, 100.0f);
	registry.emplace<Render>(entity, std::move(object));
	registry.emplace<EnemyTag>(entity, type);
	registry.emplace<ShouldDestroy>(entity);

	return entity;
}

entt::entity createBullet(entt::registry& registry, std::shared_ptr<Model> object, glm::vec3& position, glm::vec3 rotate) {
	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, position, rotate);
	registry.emplace<Velocity>(entity);
	registry.emplace<Render>(entity, object);
	registry.emplace<ShouldDestroy>(entity);
	registry.emplace<BulletTag>(entity);

	return entity;
}
