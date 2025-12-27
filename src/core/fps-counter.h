#pragma once

#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <cstddef>

class FpsCounter {
public:
    void update(const double dt);

    [[nodiscard]] double getFps() const {
        return m_fps;
    }

private:
    std::size_t m_frameCount{};
    double m_accumulatedTime{};
    double m_fps{};
};

#endif // FPS_COUNTER_H
