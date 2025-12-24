#include "audio-engine.h"

#include <stdexcept>
#include <utility>

AudioEngine::AudioEngine() {
    if (ma_engine_init(NULL, &m_engine) != MA_SUCCESS) {
        throw std::runtime_error("Failed to initialize audio engine");
    }
}

AudioEngine::AudioEngine(AudioEngine&& other) noexcept
    : m_engine{ std::exchange(other.m_engine, {}) } {}

AudioEngine& AudioEngine::operator=(AudioEngine&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    ma_engine_uninit(&m_engine);
    m_engine = std::exchange(other.m_engine, {});

    return *this;
}
