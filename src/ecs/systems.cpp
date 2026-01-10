#include "systems.h"

#include "entities.h"

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

void playerInputSystem(entt::registry& registry, const InputManager& inputManager, std::shared_ptr<Model> object, const float deltaTime) {
	constexpr float animationTime = 0.3f;

	auto view = registry.view<PlayerTag, Transform>();

	for (auto [entity, playerTag, transform] : view.each()) {

		if (playerTag.animationTime <= 0.0f) {
			Lane::Lane newLane{playerTag.currentLane};
			bool shouldMove{ false };

			bool aPressed{ inputManager.isDown(inputManager.Key::A) };
			bool dPressed{ inputManager.isDown(inputManager.Key::D) };

			if (aPressed && !dPressed) { 
				newLane = Lane::changeLane(playerTag.currentLane, false);
				shouldMove = true;
			}
			else if (!aPressed && dPressed) {
				newLane = Lane::changeLane(playerTag.currentLane, true);
				shouldMove = true;
			}

			if (shouldMove) {
				playerTag.targetLane = newLane;
				playerTag.animationTime = animationTime;
				playerTag.startX = transform.position.x;
				playerTag.targetX = Lane::getLaneXPosition(newLane);
			}

			if (playerTag.canShoot() && inputManager.isDown(inputManager.Key::Space)) {
				createBullet(registry, object, transform.position, transform.rotate);
			}
		}

		if (playerTag.animationTime > 0.f) {
			playerTag.animationTime -= deltaTime;

			if (playerTag.animationTime <= 0.f) {
				playerTag.animationTime = 0.f;
				playerTag.currentLane = playerTag.targetLane;
				transform.position.x = playerTag.targetX;
			}
			else {
				float t{ 1.f - (playerTag.animationTime / animationTime) };
				transform.position.x = playerTag.startX + (playerTag.targetX - playerTag.startX) * t;
			}
		}
	};
}

void cleanUpSystem(entt::registry& registry) {
	entt::basic_view view = registry.view<ShouldDestroy>();
	
	for (auto [entity, shouldDestroy] : view.each()) {
		if (!shouldDestroy.shuld)
			continue;

		registry.destroy(entity);
	}
}