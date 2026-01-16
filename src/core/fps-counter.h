#pragma once

#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <cstddef>

/**
 * @brief Utility class for calculating frames per second.
 *
 * Accumulates frame time and frame count to compute
 * average FPS over time.
 */
class FpsCounter {
public:
    /**
     * @brief Updates the FPS calculation.
     *
     * Should be called once every frame.
     *
     * @param dt Delta time in seconds since the last update.
     */
    void update(const double dt);

    /**
     * @brief Returns the current calculated FPS.
     * @return Frames per second.
     */
    [[nodiscard]] double getFps() const {
        return m_fps;
    }

private:
    std::size_t m_frameCount{};
    double m_accumulatedTime{};
    double m_fps{};
};

#endif // FPS_COUNTER_H
