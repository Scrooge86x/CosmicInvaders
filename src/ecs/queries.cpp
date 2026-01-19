#include "queries.h"

bool isPlayerAlive(const entt::registry& registry) {
    auto player{ registry.view<PlayerTag>().front() };
    return registry.get<Health>(player).current > 0;
}

bool enemyExists(const entt::registry& registry) {
    return registry.view<EnemyTag>().begin() != registry.view<EnemyTag>().end();
}

Health getPlayerHealth(const entt::registry& registry) {
    auto player{ registry.view<PlayerTag>().front() };
    return registry.get<Health>(player);
}

Stats getPlayerStats(const entt::registry& registry) {
    auto player{ registry.view<PlayerTag>().front() };
    return registry.get<Stats>(player);
}