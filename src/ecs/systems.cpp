#include "systems.h"
#include <renderer/renderer.h>

void movementSystem(entt::registry& registry) {
	entt::basic_view view = registry.view<Transform, Velocity>();

	for (auto [entity, transform, velocity]: view.each()) {
		transform.position += velocity.linear;
	}
}

void renderingSystem(entt::registry& registry, Renderer& renderer, glm::mat4& model) {
	entt::basic_view view = registry.view<Render>();

	for (auto [entity, render] : view.each()) {
		renderer.draw(*render.object, model);
	}
}

void playerDirectionSystem(entt::registry& registry, const Direction direction) {
	entt::basic_view entitie = registry.view<PlayerTag>();

	if (!entitie.empty()) {
		auto player = *entitie.begin();

		auto& transform = registry.get<Transform>(player);
		transform.position.x = direction;
	}
}

void cleanUpSystem(entt::registry& registry) {
	entt::basic_view view = registry.view<ShouldDestroy>();
	
	for (auto [entity, shouldDestroy] : view.each()) {
		if (!shouldDestroy.shuld)
			continue;

		registry.destroy(entity);
	}
}