#pragma once

#ifndef GAME_H
#define GAME_H

#include <core/audio-engine.h>
#include <core/fps-counter.h>
#include <core/input-manager.h>
#include <core/settings.h>

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
    Game() = default;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    double getFps() const { return m_fpsCounter.getFps(); }
    const Settings& getSettings() const { return m_settings; }
    const Camera& getCamera() const { return m_camera; }
    const Lighting& getLighting() const { return m_lighting; }

    void setState(const GameState newState) { m_gameState = newState; }
    GameState getState() const { return m_gameState; }

private:
    AudioEngine m_audioEngine{};
    FpsCounter m_fpsCounter{};
    InputManager m_inputManager{};
    Settings m_settings{ "config.json" };

    Camera m_camera{};
    ModelStore m_modelStore{};
    Lighting m_lighting{};

    GameState m_gameState{ GameState::MainMenu };
};

#endif // GAME_H
