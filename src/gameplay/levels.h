#pragma once

#ifndef LEVELS_H
#define LEVELS_H

#include <array>
#include <vector>

#include <ecs/entities.h>

namespace gameplay {
	struct EnemySpawnData {
		EnemyType enemyType;
		double spawnTime;
		Lane::Lane lane;
	};

	struct Level {
		std::vector<EnemySpawnData> spawns;
	};

	const std::size_t levelsCount{ 3 };

	inline std::array<Level, levelsCount> levels = {
		Level{{
			{ EnemyType::Basic, 1000, Lane::Lane::Left },
			{ EnemyType::Basic, 4000, Lane::Lane::Right },
			{ EnemyType::Basic, 4500, Lane::Lane::Middle },
			{ EnemyType::Basic, 5500, Lane::Lane::Middle },
			{ EnemyType::Basic, 5500, Lane::Lane::Left },
			{ EnemyType::Slim, 7000, Lane::Lane::Right },
			{ EnemyType::Basic, 8000, Lane::Lane::Left },
			{ EnemyType::Slim, 8500, Lane::Lane::Middle },
			{ EnemyType::Basic, 10000, Lane::Lane::Right },
			{ EnemyType::Basic, 11000, Lane::Lane::Left },
			{ EnemyType::Bulky, 13000, Lane::Lane::Middle },
		}},

		Level{{
			{ EnemyType::Bulky, 1000, Lane::Lane::Right },
			{ EnemyType::Slim, 3000, Lane::Lane::Left },
			{ EnemyType::Basic, 5000, Lane::Lane::Middle },
			{ EnemyType::Basic, 7000, Lane::Lane::Right },
			{ EnemyType::Basic, 9000, Lane::Lane::Middle },
			{ EnemyType::Bulky, 11000, Lane::Lane::Left },
			{ EnemyType::Basic, 13000, Lane::Lane::Middle },
			{ EnemyType::Slim, 15000, Lane::Lane::Left },
			{ EnemyType::Basic, 17000, Lane::Lane::Right },
			{ EnemyType::Basic, 19000, Lane::Lane::Middle },
			{ EnemyType::Basic, 21000, Lane::Lane::Left },
			{ EnemyType::Slim, 23000, Lane::Lane::Left },
			{ EnemyType::Bulky, 25000, Lane::Lane::Right },
			{ EnemyType::Slim, 27000, Lane::Lane::Middle },
			{ EnemyType::Basic, 29000, Lane::Lane::Left },
			{ EnemyType::Bulky, 31000, Lane::Lane::Middle },
		}},

		Level{{
			{ EnemyType::Bulky, 1000, Lane::Lane::Right },
			{ EnemyType::Slim, 3000, Lane::Lane::Left },
			{ EnemyType::Basic, 5000, Lane::Lane::Middle },
			{ EnemyType::Basic, 7000, Lane::Lane::Right },
			{ EnemyType::Basic, 9000, Lane::Lane::Middle },
			{ EnemyType::Bulky, 11000, Lane::Lane::Left },
			{ EnemyType::Basic, 13000, Lane::Lane::Middle },
			{ EnemyType::Slim, 15000, Lane::Lane::Left },
			{ EnemyType::Basic, 17000, Lane::Lane::Right },
			{ EnemyType::Basic, 19000, Lane::Lane::Middle },
			{ EnemyType::Basic, 21000, Lane::Lane::Left },
			{ EnemyType::Slim, 23000, Lane::Lane::Left },
			{ EnemyType::Bulky, 25000, Lane::Lane::Right },
			{ EnemyType::Slim, 27000, Lane::Lane::Middle },
			{ EnemyType::Basic, 29000, Lane::Lane::Left },
			{ EnemyType::Bulky, 31000, Lane::Lane::Middle },
			{ EnemyType::Basic, 33000, Lane::Lane::Left },
			{ EnemyType::Basic, 35000, Lane::Lane::Right },
			{ EnemyType::Slim, 37000, Lane::Lane::Middle },
			{ EnemyType::Basic, 39000, Lane::Lane::Left },
			{ EnemyType::Basic, 41000, Lane::Lane::Left },
			{ EnemyType::Basic, 43000, Lane::Lane::Middle },
			{ EnemyType::Bulky, 45000, Lane::Lane::Left },
			{ EnemyType::Bulky, 47000, Lane::Lane::Right },
		}}
	};
}

#endif LEVELS_H // !LEVELS_H