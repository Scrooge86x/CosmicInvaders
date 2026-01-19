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
    constexpr float bulletDelay{ 1.0f };

    auto player{ registry.view<PlayerTag>().front() };
    Animation& animation{ registry.get<Animation>(player) };
    Transform& transform{ registry.get<Transform>(player) };
    TimeDelay& timeDelay{ registry.get<TimeDelay>(player) };
    Stats& stats{ registry.get<Stats>(player) };

    if (animation.animationTime <= 0.0f) {
        Lane::Lane newLane{animation.currentLane};

        bool aPressed{ inputManager.isDown(InputManager::Key::A) };
        bool dPressed{ inputManager.isDown(InputManager::Key::D) };

        if (aPressed && !dPressed) {
            newLane = Lane::changeLane(animation.currentLane, Lane::LaneDirection::Left);
        }
        else if (!aPressed && dPressed) {
            newLane = Lane::changeLane(animation.currentLane, Lane::LaneDirection::Right);
        }

        if (newLane != animation.currentLane) {
            animation.targetLane = newLane;
            animation.animationTime = animationTime;
        }

        if (timeDelay.shootingDelay > 0.0f) {
            timeDelay.shootingDelay -= deltaTime;
        }

        if (inputManager.isDown(InputManager::Key::Space) && timeDelay.shootingDelay <= 0.0f) {
            std::cout << "Działa\n";
            constexpr auto path{ "assets/3d-models/bullet.obj" };
            glm::vec3 velocity{ 0.0f, 0.0f, -1.0f };
            createBullet(registry, EntityTypes::Player, modelStore.load(path, 0.1f), transform.position, glm::vec3{-90.0f, 0.0f, 0.0f}, velocity);
            timeDelay.shootingDelay = bulletDelay;
            stats.firedBullets += 1;
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
}

void restorePlayerHealthSystem(entt::registry& registry) {
    auto player = registry.view<PlayerTag>().front();
    Health& health{ registry.get<Health>(player) };
    health.current = health.max;
}

void receivingDamageSystem(entt::registry& registry, const float deltaTime) {
    constexpr float invincibilityTime{ 1.0f };

    auto player = registry.view<PlayerTag>().front();
    Health& health{ registry.get<Health>(player) };
    TimeDelay& timeDelay{ registry.get<TimeDelay>(player) };
    Transform transform{ registry.get<Transform>(player) };
    Stats& stats{ registry.get<Stats>(player) };


    auto enemy = registry.view<EnemyTag, Transform, Damage, Health, ShouldDestroy>();
    auto enemyBullet = registry.view<EnemyBulletTag, Transform, Damage, ShouldDestroy>();
    auto playerBullet = registry.view<PlayerBulletTag, Transform, Damage, ShouldDestroy>();

    for (auto [enemyEntity, enemyTransform, damage, enemyHealth, shouldDestroy] : enemy.each()) {
        for (auto [bulletEntity, bulletTransform, bulletDamage, bulletShouldDestroy] : playerBullet.each()) {
            if (bulletTransform.position.z < -40) {
                bulletShouldDestroy.shuld = true;
                continue;
            }

            if (enemyTransform.position.z < bulletTransform.position.z) {
                continue;
            }

            if (enemyTransform.position.x != bulletTransform.position.x) {
                continue;
            }

            enemyHealth.current -= bulletDamage.current;
            bulletShouldDestroy.shuld = true;

            stats.damageDealt += bulletDamage.current;

            if (enemyHealth.current <= 0) {
                shouldDestroy.shuld = true;
            }
        }
    }

    if (timeDelay.recievingDamageDelay > 0.0f) {
        timeDelay.recievingDamageDelay -= deltaTime;
    }

    if (timeDelay.recievingDamageDelay > 0.0f) {
        return;
    }

    // Player recieving damage from enemys bullet.
    for (auto [bulletEntity, bulletTransform, damage, shouldDestroy] : enemyBullet.each()) {
        if (bulletTransform.position.z > 0) {
            shouldDestroy.shuld = true;
            continue;
        }
        if (bulletTransform.position.z > -4) {
            continue;
        }

        if (bulletTransform.position.z <= transform.position.z) {
            continue;
        }

        if (transform.position.x != bulletTransform.position.x) {
            continue;
        }

        std::cout << "bullet: " << bulletTransform.position.z << "\n";

        health.current -= damage.current;
        timeDelay.recievingDamageDelay = invincibilityTime;

        stats.lostHealth += damage.current;

        shouldDestroy.shuld = true;
    }

    if (timeDelay.recievingDamageDelay > 0.0f) {
        return;
    }

    // Player recieving damage from enemy
    for (auto [enemyEntity, enemyTransform, damage, enemyHealth, shouldDestroy] : enemy.each()) {
        int additionalDmg{};

        if (transform.position.x != enemyTransform.position.x) {
            if (enemyTransform.position.z < -2) {
                continue;
            }
            additionalDmg = 20;
        }

        if (enemyTransform.position.z < transform.position.z) {
            continue;
        }

        //std::cout << enemyTransform.position.z << " " << transform.position.z << "\n";

        health.current -= damage.current + additionalDmg;
        timeDelay.recievingDamageDelay = invincibilityTime;

        stats.lostHealth += damage.current + additionalDmg;

        shouldDestroy.shuld = true;
    }
}

void enemyShootingSystem(entt::registry& registry, ModelStore& modelStore, const float deltaTime) {
    constexpr float delay{ 1.0f };

    auto enemy = registry.view<EnemyTag, TimeDelay, Transform>();

    for (auto [enemyEntity, timeDelay, transform] : enemy.each()) {
        if (timeDelay.shootingDelay > 0.0f) {
            timeDelay.shootingDelay -= deltaTime;
            continue;
        }

        timeDelay.shootingDelay = getRandomDelay(2.0f, 3.0f);

        constexpr auto path{ "assets/3d-models/bullet.obj" };
        glm::vec3 velocity{0.0f, 0.0f, 2.0f};

        createBullet(registry, EntityTypes::Enemy, modelStore.load(path, 0.1f), transform.position, glm::vec3{90.0f, 0.0f, 0.0f}, velocity);

    }
}

float getRandomDelay(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distrib(min, max);
    float rawNumber = distrib(gen);

    return std::round(rawNumber * 10) / 10.0f;
}