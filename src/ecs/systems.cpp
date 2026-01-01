#include "systems.h"
#include <renderer/renderer.h>
#include <core/input-manager.h>

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

void playerInputSystem(entt::registry& registry, const InputManager& inputManager) {
	entt::basic_view entitie = registry.view<PlayerTag>();

	float direction{};

	if (inputManager.isDown(inputManager.Key::A))
		direction -= 1;

	if (inputManager.isDown(inputManager.Key::D))
		direction += 1;

	if (!entitie.empty()) {
		auto player = *entitie.begin();

		auto& velocity = registry.get<Velocity>(player);
		velocity.linear.x = direction;
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