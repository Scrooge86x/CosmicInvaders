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

void cleanUpSystem(entt::registry& registry) {
	entt::basic_view view = registry.view<ShouldDestroy>();
	
	for (auto [entity, shouldDestroy] : view.each()) {
		if (!shouldDestroy.shuld)
			continue;

		registry.destroy(entity);
	}
}