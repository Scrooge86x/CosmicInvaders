#include "entities.h"
#include <renderer/model.h>

entt::entity createPlayer(entt::registry& registry, std::shared_ptr<Model> object) {
	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f));
	registry.emplace<Health>(entity, 10.0f, 10.0f);
	registry.emplace<Render>(entity, object);
	registry.emplace<Animation>(entity);
	registry.emplace<PlayerTag>(entity);

	return entity;
}

entt::entity createEntity(entt::registry& registry, std::shared_ptr<Model> object, glm::vec3& position, std::string& type) {

	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, position);
	registry.emplace<Velocity>(entity);
	registry.emplace<Health>(entity, 5.0f, 5.0f);
	registry.emplace<Render>(entity, std::move(object));
	registry.emplace<Damage>(entity, 3.0f);
	registry.emplace<EnemyTag>(entity);
	registry.emplace<ShouldDestroy>(entity);

	return entity;
}

entt::entity createBullet(entt::registry& registry, const EntityTypes fromWho, std::shared_ptr<Model> object, glm::vec3& position, glm::vec3 direction) {
	entt::entity entity = registry.create();

	registry.emplace<Transform>(entity, position, direction);
	registry.emplace<Velocity>(entity);
	registry.emplace<Render>(entity, object);
	registry.emplace<ShouldDestroy>(entity);
	registry.emplace<Damage>(entity);
	registry.emplace<FromWho>(entity, fromWho);
	registry.emplace<BulletTag>(entity);

	return entity;
}
