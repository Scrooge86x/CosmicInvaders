#pragma once

#ifndef LEVELS_H
#define LEVELS_H

#include <array>
#include <utility>

#include <ecs/entities.h>

namespace gameplay {
	struct EnemySpawnData {
		EnemyType enemyType{};
		double spawnTime{};
		Lane::Lane lane{};
	};

	template <std::size_t N>
	struct Level {
		consteval Level(const EnemySpawnData(&arr)[N]) {
			for (std::size_t i{}; i < N; ++i) {
				spawns[i] = arr[i];
			}
		}

		std::array<EnemySpawnData, N> spawns{};
	};

	struct LevelView {
		template <std::size_t N>
		constexpr LevelView(const Level<N>& level)
			: spawns{ level.spawns }
		{}

		std::span<const EnemySpawnData> spawns{};
	};

	template <typename... Ts>
	class LevelList {
	public:
		using TupleType = std::tuple<Ts...>;

		consteval LevelList(Ts&&... levels)
			: m_levels{ std::forward<Ts>(levels)... }
		{}

		[[nodiscard]] LevelView operator[](const std::size_t index) const {
			static constexpr auto getterTable = []<std::size_t... Is>(std::index_sequence<Is...>) {
				using GetterFn = LevelView(*)(const TupleType&);
				return std::array<GetterFn, sizeof...(Ts)>{
					(&get<Is>)...
				};
			}(std::index_sequence_for<Ts...>{});

			return getterTable[index](m_levels);
		}

		[[nodiscard]] std::size_t size() const {
			return sizeof...(Ts);
		}

	private:
		template <std::size_t I>
		static constexpr LevelView get(const TupleType& tuple) {
			return std::get<I>(tuple);
		}

		TupleType m_levels{};
	};

	inline constexpr LevelList levels{
		Level{{
			{ EnemyType::Basic,  1000, Lane::Lane::Left   },
			{ EnemyType::Basic,  4000, Lane::Lane::Right  },
			{ EnemyType::Basic,  4500, Lane::Lane::Middle },
			{ EnemyType::Basic,  5500, Lane::Lane::Middle },
			{ EnemyType::Basic,  5500, Lane::Lane::Left   },
			{ EnemyType::Slim,   7000, Lane::Lane::Right  },
			{ EnemyType::Basic,  8000, Lane::Lane::Left   },
			{ EnemyType::Slim,   8500, Lane::Lane::Middle },
			{ EnemyType::Basic, 10000, Lane::Lane::Right  },
			{ EnemyType::Basic, 11000, Lane::Lane::Left   },
			{ EnemyType::Bulky, 13000, Lane::Lane::Middle },
		}},

		Level{{
			{ EnemyType::Bulky,  1000, Lane::Lane::Right  },
			{ EnemyType::Slim,   3000, Lane::Lane::Left   },
			{ EnemyType::Basic,  5000, Lane::Lane::Middle },
			{ EnemyType::Basic,  7000, Lane::Lane::Right  },
			{ EnemyType::Basic,  9000, Lane::Lane::Middle },
			{ EnemyType::Bulky, 11000, Lane::Lane::Left   },
			{ EnemyType::Basic, 13000, Lane::Lane::Middle },
			{ EnemyType::Slim,  15000, Lane::Lane::Left   },
			{ EnemyType::Basic, 17000, Lane::Lane::Right  },
			{ EnemyType::Basic, 19000, Lane::Lane::Middle },
			{ EnemyType::Basic, 21000, Lane::Lane::Left   },
			{ EnemyType::Slim,  23000, Lane::Lane::Left   },
			{ EnemyType::Bulky, 25000, Lane::Lane::Right  },
			{ EnemyType::Slim,  27000, Lane::Lane::Middle },
			{ EnemyType::Basic, 29000, Lane::Lane::Left   },
			{ EnemyType::Bulky, 31000, Lane::Lane::Middle },
		}},

		Level{{
			{ EnemyType::Bulky,  1000, Lane::Lane::Right  },
			{ EnemyType::Slim,   3000, Lane::Lane::Left   },
			{ EnemyType::Basic,  5000, Lane::Lane::Middle },
			{ EnemyType::Basic,  7000, Lane::Lane::Right  },
			{ EnemyType::Basic,  9000, Lane::Lane::Middle },
			{ EnemyType::Bulky, 11000, Lane::Lane::Left   },
			{ EnemyType::Basic, 13000, Lane::Lane::Middle },
			{ EnemyType::Slim,  15000, Lane::Lane::Left   },
			{ EnemyType::Basic, 17000, Lane::Lane::Right  },
			{ EnemyType::Basic, 19000, Lane::Lane::Middle },
			{ EnemyType::Basic, 21000, Lane::Lane::Left   },
			{ EnemyType::Slim,  23000, Lane::Lane::Left   },
			{ EnemyType::Bulky, 25000, Lane::Lane::Right  },
			{ EnemyType::Slim,  27000, Lane::Lane::Middle },
			{ EnemyType::Basic, 29000, Lane::Lane::Left   },
			{ EnemyType::Bulky, 31000, Lane::Lane::Middle },
			{ EnemyType::Basic, 33000, Lane::Lane::Left   },
			{ EnemyType::Basic, 35000, Lane::Lane::Right  },
			{ EnemyType::Slim,  37000, Lane::Lane::Middle },
			{ EnemyType::Basic, 39000, Lane::Lane::Left   },
			{ EnemyType::Basic, 41000, Lane::Lane::Left   },
			{ EnemyType::Basic, 43000, Lane::Lane::Middle },
			{ EnemyType::Bulky, 45000, Lane::Lane::Left   },
			{ EnemyType::Bulky, 47000, Lane::Lane::Right  },
		}}
	};
}

#endif LEVELS_H // !LEVELS_H
