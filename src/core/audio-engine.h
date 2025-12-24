#pragma once

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <miniaudio.h>

class AudioEngine {
public:
    AudioEngine();

    ~AudioEngine() {
        ma_engine_uninit(&m_engine);
    }

    AudioEngine(const AudioEngine&) = delete;
    AudioEngine& operator=(const AudioEngine&) = delete;

    AudioEngine(AudioEngine&& other) noexcept;
    AudioEngine& operator=(AudioEngine&& other) noexcept;

    void play(const char* const path) {
        ma_engine_play_sound(&m_engine, path, NULL);
    }

private:
    ma_engine m_engine{};
};

#endif // AUDIO_ENGINE_H
