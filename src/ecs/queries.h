#pragma once

#ifndef QUERIES_H
#define QUERIES_H

#include <entt/entity/registry.hpp>

struct Stats;

bool isPlayerAlive(const entt::registry& registry);
bool enemyExists(const entt::registry& registry);

float getPlayerHealth(const entt::registry& registry);
Stats getPlayerStats(const entt::registry& registry);

#endif // !QUERIES_H