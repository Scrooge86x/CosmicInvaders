#pragma once

#ifndef TIMER_H
#define TIMER_H

#include <concepts>

/**
 * @brief Measures delta time between updates.
 */
class Timer {
public:
    /**
     * @brief Updates the current delta time based on the previous timestamp.
     *
     * This function should be called once per frame to measure the time between frames.
     */
    void update();

    /**
     * @brief Returns the stored delta time from the last update, does NOT recompute it.
     *
     * @tparam T Floating point type to return the value as.
     * @return Delta time in seconds.
     */
    template <std::floating_point T>
    [[nodiscard]] T getDt() const {
        return static_cast<T>(m_dt);
    }

private:
    double m_prevTimestamp{};
    double m_dt{};
};

#endif // TIMER_H
