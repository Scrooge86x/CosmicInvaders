#include "entities.h"
#include <renderer/model.h>
#include <renderer/model-store.h>

entt::entity createPlayer(entt::registry& registry, std::shared_ptr<Model> object, const glm::vec3& position) {
    entt::entity entity = registry.create();

    registry.emplace<Transform>(entity, position, glm::vec3{ 0.f, -90.f, 0.f });
    registry.emplace<Health>(entity, 100, 100);
    registry.emplace<Render>(entity, object);
    registry.emplace<Animation>(entity);
    registry.emplace<TimeDelay>(entity);
    registry.emplace<PlayerTag>(entity);
    registry.emplace<Stats>(entity);

    return entity;
}

entt::entity createEntity(entt::registry& registry, EnemyType enemyType, ModelStore& modelStore, Lane::lane& lane) {

    entt::entity entity = registry.create();
    std::shared_ptr<Model> object;
    glm::vec3 position{ Lane::getLaneXPosition(lane), -2.0f, -40.0f};
    glm::vec3 velocity{0.0f, 0.0f, 0.4f};
    int health{ 50 };

    constexpr auto basicEnemy{ "assets/3d-models/Battle-SpaceShip-Free-3D-Low-Poly-Models/Destroyer_01.fbx" };
    constexpr auto slimEnemy{ "assets/3d-models/Battle-SpaceShip-Free-3D-Low-Poly-Models/Light_cruiser_05.fbx" };
    constexpr auto bulkyEnemy{ "assets/3d-models/Battle-SpaceShip-Free-3D-Low-Poly-Models/Destroyer_04.fbx" };

    switch (enemyType) {
    case EnemyType::Basic:
        object = modelStore.load(basicEnemy, 0.0003f);
        break;
    case EnemyType::Slim:
        object = modelStore.load(slimEnemy, 0.0003f);
        velocity.z = 1.5f;
        health = 30;
        break;
    case EnemyType::Bulky:
        object = modelStore.load(bulkyEnemy, 0.0003f);
        velocity.z = 0.1f;
        health = 80;
        break;
    default:
        break;
    }

    registry.emplace<Transform>(entity, position, glm::vec3{0.f, 90.f, 0.f});
    registry.emplace<Velocity>(entity, velocity);
    registry.emplace<Health>(entity, health, health);
    registry.emplace<Render>(entity, std::move(object));
    registry.emplace<Damage>(entity, 30);
    registry.emplace<TimeDelay>(entity);
    registry.emplace<Stats>(entity);
    registry.emplace<EnemyTag>(entity);
    registry.emplace<ShouldDestroy>(entity);

    return entity;
}

entt::entity createBullet(entt::registry& registry, const EntityTypes fromWho, std::shared_ptr<Model> object, glm::vec3& position, const glm::vec3& rotation, const glm::vec3& velocity) {
    entt::entity entity = registry.create();
    int damage{ 10 };

    if (fromWho == EntityTypes::Enemy) {
        registry.emplace<EnemyBulletTag>(entity);
    }
    else {
        registry.emplace<PlayerBulletTag>(entity);
        damage = 30;
    }

    registry.emplace<Transform>(entity, position, rotation);
    registry.emplace<Velocity>(entity, velocity);
    registry.emplace<Render>(entity, object);
    registry.emplace<ShouldDestroy>(entity);
    registry.emplace<Damage>(entity, damage);


    return entity;
}
