#pragma once

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <miniaudio.h>

/**
 * @brief High-level wrapper around miniaudio engine.
 *
 * Responsible for initializing and managing a global audio engine
 * and playing audio files by path.
 *
 * The engine owns the underlying miniaudio engine instance
 * and guarantees proper shutdown on destruction.
 */
class AudioEngine {
public:
    /**
     * @brief Constructs and initializes miniaudio engine.
     */
    AudioEngine();

    /**
     * @brief Destroys the audio engine and releases all resources.
     */
    ~AudioEngine() {
        ma_engine_uninit(&m_engine);
    }

    AudioEngine(const AudioEngine&) = delete;
    AudioEngine& operator=(const AudioEngine&) = delete;

    AudioEngine(AudioEngine&& other) noexcept;
    AudioEngine& operator=(AudioEngine&& other) noexcept;

    /**
     * @brief Plays an audio file.
     *
     * The sound is played immediately using the internal engine.
     *
     * @param path Path to the audio file.
     */
    void play(const char* const path) {
        ma_engine_play_sound(&m_engine, path, NULL);
    }

private:
    ma_engine m_engine{};
};

#endif // AUDIO_ENGINE_H
