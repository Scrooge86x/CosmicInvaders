#pragma once

#ifndef GAME_H
#define GAME_H

#include <core/audio-engine.h>
#include <core/fps-counter.h>
#include <core/input-manager.h>
#include <core/settings.h>
#include <core/timer.h>

#include <renderer/camera.h>
#include <renderer/model-store.h>
#include <renderer/lighting.h>

#include <entt/entity/registry.hpp>

class Renderer;
enum class EnemyType;

enum class GameState {
    MainMenu,
    Playing,
    Paused,
    GameOver,
};

class Game {
public:
    Game(InputManager& inputManager);

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    void update(const double dt);
    void render(Renderer& renderer);
    void requestQuit() { m_shouldQuit = true; }

    [[nodiscard]] double getFps() const { return m_fpsCounter.getFps(); }
    [[nodiscard]] const Settings& getSettings() const { return m_settings; }
    [[nodiscard]] Settings& getSettings() { return m_settings; }
    [[nodiscard]] const Camera& getCamera() const { return m_camera; }
    [[nodiscard]] Camera& getCamera() { return m_camera; }
    [[nodiscard]] const Lighting& getLighting() const { return m_lighting; }
    [[nodiscard]] std::size_t getCurrentLevel() const { return m_currentLevel; }
    [[nodiscard]] const entt::registry& getRegistry() const { return m_registry; }
    [[nodiscard]] bool shouldQuit() const { return m_shouldQuit; }

    void setState(const GameState newState) { m_gameState = newState; }
    [[nodiscard]] GameState getState() const { return m_gameState; }

    void loadPlayer();

private:
    void updateSystems(const double dt);
    double m_timePassed{};
    std::size_t m_enemyIdx{};
    std::size_t m_currentLevel{};

    InputManager& m_inputManager;

    AudioEngine m_audioEngine{};
    FpsCounter m_fpsCounter{};
    Settings m_settings{ "config.json" };

    Camera m_camera{};
    ModelStore m_modelStore{};
    Lighting m_lighting{
        .sunPosition{ 0.f, 20.f, 0.f },
        .sunColor{ 1.f, 1.f, 3.f },
    };

    GameState m_gameState{ GameState::MainMenu };

    bool m_shouldQuit{};

    entt::registry m_registry{};
};

#endif // GAME_H
