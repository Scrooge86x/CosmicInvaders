#include "systems.h"

#include <renderer/renderer.h>
#include <renderer/model-store.h>
#include <core/input-manager.h>

#include <glm/gtc/matrix_transform.hpp>

#include <random>
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
		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3{ 1.f, 0.f, 0.f });
		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3{ 0.f, 1.f, 0.f });
		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3{ 0.f, 0.f, 1.f });

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
	constexpr float animationTime{ 0.3f };

	auto player = registry.view<Animation, Transform>();

	for (auto [entity, animation, transform] : player.each()) {

		if (animation.animationTime <= 0.0f) {
			Lane::Lane newLane{animation.currentLane};

			bool aPressed{ inputManager.isDown(inputManager.Key::A) };
			bool dPressed{ inputManager.isDown(inputManager.Key::D) };

			if (aPressed && !dPressed) { 
				newLane = Lane::changeLane(animation.currentLane, Lane::LaneDirection::Left);
			}
			else if (!aPressed && dPressed) {
				newLane = Lane::changeLane(animation.currentLane, Lane::LaneDirection::Right);
			}

			animation.targetLane = newLane;
			animation.animationTime = animationTime;

			if (animation.canShoot() && inputManager.isDown(inputManager.Key::Space)) {
				constexpr auto path{"assets/3d-models/"};
				glm::vec3 velocity{ 0.0f, 0.0f, -1.0f };
				createBullet(registry, EntityTypes::Player, modelStore.load(path, 0.0003f), transform.position, velocity);
			}
		}

		if (animation.animationTime > 0.f) {
			animation.animationTime -= deltaTime;

			if (animation.animationTime <= 0.f) {
				animation.animationTime = 0.f;
				animation.currentLane = animation.targetLane;
				transform.position.x = Lane::getLaneXPosition(animation.currentLane);
			}
			else {
				float t{ 1.f - (animation.animationTime / animationTime) };
				float startX{ Lane::getLaneXPosition(animation.currentLane) };
				float targetX{ Lane::getLaneXPosition(animation.targetLane) };

				transform.position.x = std::lerp(startX, targetX, t);
			}
		}
	};
}

void restorePlayerHealthSystem(entt::registry& registry) {
	auto player = registry.view<PlayerTag, Health>();

	for (auto [playerEntity, health] : player.each()) {
		health.current = health.max;
	}
}

bool isPlayerAliveSystem(entt::registry& registry) {
	auto player = registry.view<PlayerTag, Health>();

	for (auto [playerEntity, health] : player.each()) {
		return health.current > 0;
	}
}

void receivingDamageSystem(entt::registry& registry, const float deltaTime) {
	constexpr float invincibilityTime{ 1.0f };

	auto player = registry.view<PlayerTag, Health, TimeDelay, Transform>();
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

	for (auto [entity, health, timeDelay, transform] : player.each()) {
		if (timeDelay.time > 0.0f) {
			timeDelay.time -= deltaTime;
		}

		if (timeDelay.time > 0.0f) {
			return;
		}
	}

	for (auto [playerEntity, health, timeDelay, transform] : player.each()) {
		for (auto [bulletEntity, bulletTransform, damage, fromWho, shouldDestroy] : bullet.each()) {
			if (fromWho.fromWho == EntityTypes::Player) {
				continue;
			}

			if (transform.position.x != bulletTransform.position.x) {
				if (bulletTransform.position.z > 0) {
					shouldDestroy.shuld = true;
				}
				continue;
			}

			if (!(bulletTransform.position.z <= transform.position.z)) {
				continue;
			}

			health.current -= damage.current;
			timeDelay.time = invincibilityTime;

			shouldDestroy.shuld = true;
		}
	}

	for (auto [playerEntity, health, timeDelay, transform] : player.each()) {
		for (auto [enemyEntity, enemyTransform, damage, enemyHealth, shouldDestroy] : enemy.each()) {
			if (transform.position.x != enemyTransform.position.x) {
				continue;
			}

			if (!(enemyTransform.position.z < transform.position.z)) {
				continue;
			}

			health.current -= damage.current;
			timeDelay.time = invincibilityTime;

			shouldDestroy.shuld = true;
		}
	}
}

void enemyShootingSystem(entt::registry& registry, ModelStore& modelStore, const float deltaTime) {
	constexpr float delay{ 1.0f };
	
	auto enemy = registry.view<EnemyTag, TimeDelay, Transform>();


	for (auto [enemyEntity, timeDelay, transform] : enemy.each()) {
		if (timeDelay.time > 0.0f) {
			timeDelay.time -= deltaTime;
			continue;
		}

		timeDelay.time = getRandomDelay(2.0f, 3.0f);

		constexpr auto path{ "assets/3d-models/Battle-SpaceShip-Free-3D-Low-Poly-Models/Destroyer_01.fbx" };
		glm::vec3 velocity{0.0f, 0.0f, 2.0f};

		createBullet(registry, EntityTypes::Enemy, modelStore.load(path, 0.0003f), transform.position, velocity);

	}
}

float getRandomDelay(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> distrib(min, max);
	float rawNumber = distrib(gen);

	return std::round(rawNumber * 10) / 10.0f;
}