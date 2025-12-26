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

class Game {
public:

private:
    AudioEngine m_audioEngine{};
    FpsCounter m_fpsCounter{};
    InputManager m_inputManager{};
    Settings m_settings{ "config.json" };

    Camera m_camera{};
    ModelStore m_modelStore{};
    Lighting m_lighting{};
};

#endif // GAME_H
