#pragma once

#ifndef LEVELS_H
#define LEVELS_H

#include <ecs/entities.h>

#include <array>
#include <concepts>
#include <cstddef>
#include <utility>
#include <span>
#include <type_traits>

namespace gameplay {

    /**
     * @brief Describes a single enemy spawn.
     */
    struct EnemySpawnData {
        EnemyType enemyType{};
        double spawnTime{};
        Lane::Lane lane{};
    };

    /**
     * @brief Compile-time level definition.
     *
     * @tparam N Number of enemy spawns in the level.
     */
    template <std::size_t N>
    struct Level {
        /**
         * @brief Constructs a level from a fixed-size array of spawn data during compile time.
         */
        consteval Level(const EnemySpawnData(&spawnData)[N]) {
            for (std::size_t i{}; i < N; ++i) {
                spawns[i] = spawnData[i];
            }
        }

        std::array<EnemySpawnData, N> spawns{};
    };

    /**
     * @brief Lightweight runtime view over a level.
     *
     * Provides a uniform interface independent of the level size.
     */
    struct LevelView {
        template <std::size_t N>
        LevelView(const Level<N>& level) noexcept
            : spawns{ level.spawns }
        {}

        std::span<const EnemySpawnData> spawns{};
    };

    namespace detail {

    template <typename>
    struct IsLevel : std::false_type {};

    template <std::size_t N>
    struct IsLevel<Level<N>> : std::true_type {};

    template <typename T>
    concept LevelType = IsLevel<std::remove_cvref_t<T>>::value;

    }

    /**
     * @brief Compile time list of levels.
     *
     * Allows indexed runtime access to levels of different sizes via LevelView.
     *
     * @tparam Ts Parameter pack of Level types.
     */
    template <detail::LevelType... Ts>
    class LevelList {
    public:
        using TupleType = std::tuple<Ts...>;

        /**
         * @brief Constructs the level list during compile time from individual levels.
         *
         * @param levels Levels to store.
         */
        consteval LevelList(Ts&&... levels)
            : m_levels{ levels... }
        {}

        /**
         * @brief Access a level during runtime by index.
         *
         * @note It does NOT do any bounds checking.
         */
        [[nodiscard]] LevelView operator[](const std::size_t index) const noexcept {
            static constexpr auto getterTable = []<std::size_t... Is>(std::index_sequence<Is...>) {
                using GetterFn = LevelView(*)(const TupleType&);
                return std::array<GetterFn, sizeof...(Ts)>{
                    (&get<Is>)...
                };
            }(std::index_sequence_for<Ts...>{});

            return getterTable[index](m_levels);
        }

        [[nodiscard]] constexpr std::size_t size() const noexcept {
            return sizeof...(Ts);
        }

    private:
        template <std::size_t I>
        static constexpr LevelView get(const TupleType& tuple) noexcept {
            return std::get<I>(tuple);
        }

        TupleType m_levels{};
    };

    /**
     * @brief Global compile-time list of all game levels.
     *
     * Each entry represents a complete enemy spawn order for a level.
     */
    inline constexpr LevelList levels{
        Level{{
            { EnemyType::Basic,  1000, Lane::Lane::Left   },
            { EnemyType::Basic,  4000, Lane::Lane::Right  },
            { EnemyType::Basic,  7000, Lane::Lane::Middle },
            { EnemyType::Basic, 10000, Lane::Lane::Middle },
            { EnemyType::Basic, 13000, Lane::Lane::Left   },
            { EnemyType::Slim,  16000, Lane::Lane::Right  },
            { EnemyType::Basic, 19000, Lane::Lane::Left   },
            { EnemyType::Slim,  22000, Lane::Lane::Middle },
            { EnemyType::Basic, 25000, Lane::Lane::Right  },
            { EnemyType::Basic, 28000, Lane::Lane::Left   },
            { EnemyType::Bulky, 31000, Lane::Lane::Middle },
        }},

        Level{{
            { EnemyType::Bulky,  3000, Lane::Lane::Right  },
            { EnemyType::Slim,   6000, Lane::Lane::Left   },
            { EnemyType::Basic,  9000, Lane::Lane::Middle },
            { EnemyType::Basic, 12000, Lane::Lane::Right  },
            { EnemyType::Basic, 15000, Lane::Lane::Middle },
            { EnemyType::Bulky, 18000, Lane::Lane::Left   },
            { EnemyType::Basic, 21000, Lane::Lane::Middle },
            { EnemyType::Slim,  24000, Lane::Lane::Left   },
            { EnemyType::Basic, 27000, Lane::Lane::Right  },
            { EnemyType::Basic, 30000, Lane::Lane::Middle },
            { EnemyType::Basic, 33000, Lane::Lane::Left   },
            { EnemyType::Slim,  36000, Lane::Lane::Left   },
            { EnemyType::Bulky, 39000, Lane::Lane::Right  },
            { EnemyType::Slim,  42000, Lane::Lane::Middle },
            { EnemyType::Basic, 45000, Lane::Lane::Left   },
            { EnemyType::Bulky, 48000, Lane::Lane::Middle },
        }},

        Level{{
            { EnemyType::Bulky,  3000, Lane::Lane::Right  },
            { EnemyType::Slim,   6000, Lane::Lane::Left   },
            { EnemyType::Basic,  9000, Lane::Lane::Middle },
            { EnemyType::Basic, 12000, Lane::Lane::Right  },
            { EnemyType::Basic, 15000, Lane::Lane::Middle },
            { EnemyType::Bulky, 18000, Lane::Lane::Left   },
            { EnemyType::Basic, 21000, Lane::Lane::Middle },
            { EnemyType::Slim,  24000, Lane::Lane::Left   },
            { EnemyType::Basic, 27000, Lane::Lane::Right  },
            { EnemyType::Basic, 30000, Lane::Lane::Middle },
            { EnemyType::Basic, 33000, Lane::Lane::Left   },
            { EnemyType::Slim,  36000, Lane::Lane::Left   },
            { EnemyType::Bulky, 39000, Lane::Lane::Right  },
            { EnemyType::Slim,  42000, Lane::Lane::Middle },
            { EnemyType::Basic, 45000, Lane::Lane::Left   },
            { EnemyType::Bulky, 48000, Lane::Lane::Middle },
            { EnemyType::Basic, 51000, Lane::Lane::Left   },
            { EnemyType::Basic, 54000, Lane::Lane::Right  },
            { EnemyType::Slim,  57000, Lane::Lane::Middle },
            { EnemyType::Basic, 60000, Lane::Lane::Left   },
            { EnemyType::Basic, 63000, Lane::Lane::Left   },
            { EnemyType::Basic, 66000, Lane::Lane::Middle },
            { EnemyType::Bulky, 69000, Lane::Lane::Left   },
            { EnemyType::Bulky, 72000, Lane::Lane::Right  },
        }}
    };
}

#endif // LEVELS_H
