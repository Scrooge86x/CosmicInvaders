#include "fps-counter.h"

void FpsCounter::update(const double dt) noexcept {
    ++m_frameCount;

    m_accumulatedTime += dt;
    if (m_accumulatedTime < 1.0) {
        return;
    }

    m_fps = m_frameCount / m_accumulatedTime;
    m_frameCount = 0;
    m_accumulatedTime = 0.0;
}
