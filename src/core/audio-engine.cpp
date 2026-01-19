#include "audio-engine.h"
#include "audio-engine.h"

#include <format>
#include <stdexcept>
#include <utility>

AudioEngine::AudioEngine() {
    if (ma_engine_init(NULL, &m_engine) != MA_SUCCESS) {
        throw std::runtime_error("Failed to initialize audio engine");
    }
}

AudioEngine::~AudioEngine() {
    stopAmbient();
    ma_engine_uninit(&m_engine);
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

void AudioEngine::playAmbient(const char* const ambientPath) {
    stopAmbient();

    ma_result result{ ma_sound_init_from_file(
        &m_engine,
        ambientPath,
        MA_SOUND_FLAG_STREAM,
        NULL,
        NULL,
        &m_ambientSound
    ) };
    if (result != MA_SUCCESS) {
        throw std::runtime_error{ std::format("ma_sound_init_from_file failed with: {}", static_cast<int>(result)) };
    }

    ma_sound_set_looping(&m_ambientSound, MA_TRUE);
    ma_sound_set_volume(&m_ambientSound, 0.1f);
    ma_sound_start(&m_ambientSound);
}

void AudioEngine::stopAmbient() noexcept {
    if (!ma_sound_is_playing(&m_ambientSound)) {
        return;
    }

    ma_sound_stop(&m_ambientSound);
    ma_sound_uninit(&m_ambientSound);
}
