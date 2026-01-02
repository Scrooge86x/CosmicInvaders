#include "systems.h"
#include <renderer/renderer.h>
#include <core/input-manager.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

void movementSystem(entt::registry& registry, const float deltaTime) {
	entt::basic_view view = registry.view<Transform, Velocity>();

	const float speed{ 5.f };

	for (auto [entity, transform, velocity]: view.each()) {
		transform.position += velocity.linear * deltaTime * speed;
	}
}

void renderingSystem(entt::registry& registry, Renderer& renderer) {
	entt::basic_view view = registry.view<Render, Transform>();

	for (auto [entity, render, transform] : view.each()) {

		std::cout << transform.position.x << " " << transform.position.y << " " << transform.position.z << "\n";

		glm::mat4 model{ 1.f };
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, transform.rotate.x, glm::vec3{ 0.f, 1.f, 0.f });
		model = glm::rotate(model, transform.rotate.y, glm::vec3{ 1.f, 0.f, 0.f });
		model = glm::rotate(model, transform.rotate.z, glm::vec3{ 0.f, 0.f, 1.f });

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