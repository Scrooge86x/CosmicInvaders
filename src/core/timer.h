#pragma once

#ifndef TIMER_H
#define TIMER_H

#include <concepts>

class Timer {
public:
    void update();

    template <std::floating_point T>
    T getDt() const {
        return static_cast<T>(m_dt);
    }

private:
    double m_prevTimestamp{};
    double m_dt{};
};

#endif // TIMER_H
