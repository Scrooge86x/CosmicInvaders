#include "timer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Timer::update() noexcept {
    const double currTimestamp{ glfwGetTime() };
    m_dt = currTimestamp - m_prevTimestamp;
    m_prevTimestamp = currTimestamp;
}
