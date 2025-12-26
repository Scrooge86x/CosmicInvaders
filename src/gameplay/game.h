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

    void update();
    void requestQuit() { m_shouldQuit = true; }

    double getFps() const { return m_fpsCounter.getFps(); }
    const Settings& getSettings() const { return m_settings; }
    const Camera& getCamera() const { return m_camera; }
    const Lighting& getLighting() const { return m_lighting; }
    bool shouldQuit() const { return m_shouldQuit; }

    void setState(const GameState newState) { m_gameState = newState; }
    GameState getState() const { return m_gameState; }

private:
    InputManager& m_inputManager;

    AudioEngine m_audioEngine{};
    FpsCounter m_fpsCounter{};
    Settings m_settings{ "config.json" };
    Timer m_timer{};

    Camera m_camera{};
    ModelStore m_modelStore{};
    Lighting m_lighting{};

    GameState m_gameState{ GameState::MainMenu };

    bool m_shouldQuit{};
};

#endif // GAME_H
