#include "systems.h"

void movementSystem(entt::registry& registry) {
	entt::basic_view view = registry.view<Transform, Velocity>();

	for (auto [entity, transform, velocity]: view.each()) {
		transform.position += velocity.linear * velocity.speed;
	}
}

void renderingSystem(entt::registry& registry, Shader& shader, glm::mat4& model) {
	entt::basic_view view = registry.view<Render>();

	for (auto [entity, render] : view.each()) {
		//ImmediateRenderer renderer{ ImmediateRenderer::getInstance };
		//renderer.submit(render.object, shader, model);
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