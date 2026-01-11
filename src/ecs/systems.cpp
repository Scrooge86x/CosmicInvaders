#include "systems.h"

#include <renderer/renderer.h>
#include <renderer/model-store.h>
#include <core/input-manager.h>

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

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

		//std::cout << transform.position.x << " " << transform.position.y << " " << transform.position.z << "\n";

		glm::mat4 model{ 1.f };
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, transform.rotate.x, glm::vec3{ 0.f, 1.f, 0.f });
		model = glm::rotate(model, transform.rotate.y, glm::vec3{ 1.f, 0.f, 0.f });
		model = glm::rotate(model, transform.rotate.z, glm::vec3{ 0.f, 0.f, 1.f });

		renderer.draw(*render.object, model);
	}
}

void cleanUpSystem(entt::registry& registry) {
	entt::basic_view view = registry.view<ShouldDestroy>();
	
	for (auto [entity, shouldDestroy] : view.each()) {
		if (shouldDestroy.shuld)
			registry.destroy(entity);
	}
}

void playerInputSystem(entt::registry& registry, const InputManager& inputManager, ModelStore& modelStore, const float deltaTime) {
	constexpr float animationTime = 0.3f;

	auto view = registry.view<Animation, Transform>();

	for (auto [entity, player, transform] : view.each()) {

		if (player.animationTime <= 0.0f) {
			Lane::Lane newLane{player.currentLane};

			bool aPressed{ inputManager.isDown(inputManager.Key::A) };
			bool dPressed{ inputManager.isDown(inputManager.Key::D) };

			if (aPressed && !dPressed) { 
				newLane = Lane::changeLane(player.currentLane, Lane::LaneDirection::Left);
			}
			else if (!aPressed && dPressed) {
				newLane = Lane::changeLane(player.currentLane, Lane::LaneDirection::Right);
			}

			player.targetLane = newLane;
			player.animationTime = animationTime;

			if (player.canShoot() && inputManager.isDown(inputManager.Key::Space)) {
				constexpr auto path{"assets/3d-models/"};
				createBullet(registry, EntityTypes::Player, modelStore.load(path, 0.0003f), transform.position);
			}
		}

		if (player.animationTime > 0.f) {
			player.animationTime -= deltaTime;

			if (player.animationTime <= 0.f) {
				player.animationTime = 0.f;
				player.currentLane = player.targetLane;
				transform.position.x = Lane::getLaneXPosition(player.currentLane);
			}
			else {
				float t{ 1.f - (player.animationTime / animationTime) };
				float startX{ Lane::getLaneXPosition(player.currentLane) };
				float targetX{ Lane::getLaneXPosition(player.targetLane) };

				transform.position.x = std::lerp(startX, targetX, t);
			}
		}
	};
}

void receivingDamageSystem(entt::registry& registry, const float deltaTime) {
	constexpr float invincibilityTime = 0.3f;

	auto player = registry.view<PlayerTag, Health, Transform>();
	auto enemy = registry.view<EnemyTag, Transform, Damage, Health, ShouldDestroy>();
	auto bullet = registry.view<BulletTag, Transform, Damage, FromWho, ShouldDestroy>();

	for (auto [enemyEntity, enemyTransform, damage, enemyHealth, shouldDestroy] : enemy.each()) {
		for (auto [bulletEntity, bulletTransform, bulletDamage, fromWho, bulletShouldDestroy] : bullet.each()) {
			if (fromWho.fromWho == EntityTypes::Enemy) {
				continue;
			}

			if (enemyTransform.position.x != enemyTransform.position.x) {
				continue;
			}

			if (!(enemyTransform.position.z > bulletTransform.position.z)) {
				continue;
			}

			enemyHealth.current -= bulletDamage.current;
			bulletShouldDestroy.shuld = true;

			if (enemyHealth.current <= 0) 
				shouldDestroy.shuld = true;
		}
	}

	for (auto [entity, health, transform] : player.each()) {
		if (health.invincibilityTime > 0.0f) {
			health.invincibilityTime -= deltaTime;
		}

		if (health.invincibilityTime > 0.0f) {
			return;
		}
	}

	for (auto [playerEntity, health, transform] : player.each()) {
		for (auto [bulletEntity, bulletTransform, damage, fromWho, shouldDestroy] : bullet.each()) {
			if (fromWho.fromWho == EntityTypes::Player) {
				continue;
			}

			if (transform.position.x != bulletTransform.position.x) {
				continue;
			}

			if (!(bulletTransform.position.z <= transform.position.z)) {
				continue;
			}

			health.current -= damage.current;
			health.invincibilityTime = 1.0f;

			shouldDestroy.shuld = true;
		}
	}

	for (auto [playerEntity, health, transform] : player.each()) {
		for (auto [enemyEntity, enemyTransform, damage, enemyHealth, shouldDestroy] : enemy.each()) {
			if (transform.position.x != enemyTransform.position.x) {
				continue;
			}

			if (!(enemyTransform.position.z < transform.position.z)) {
				continue;
			}

			health.current -= damage.current;
			health.invincibilityTime = 1.0f;

			shouldDestroy.shuld = true;
		}
	}
}

void enemyShootingSystem(entt::registry& registry) {

}

