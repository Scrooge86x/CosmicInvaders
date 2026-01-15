#pragma once

#ifndef QUERIES_H
#define QUERIES_H

#include "components.h"
#include <entt/entity/registry.hpp>

bool isPlayerAlive(const entt::registry& registry);
bool enemyExists(const entt::registry& registry);

Health getPlayerHealth(const entt::registry& registry);
Stats getPlayerStats(const entt::registry& registry);

#endif // !QUERIES_H