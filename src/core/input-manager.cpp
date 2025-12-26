#include "input-manager.h"

#include <GLFW/glfw3.h>

#include <utility>

InputManager::InputManager(GLFWwindow* const window)
    : m_window{ window }
{}

InputManager::InputManager(InputManager&& other) noexcept
    : m_window        { std::exchange(other.m_window, nullptr) }
    , m_currentStates { std::exchange(other.m_currentStates, {}) }
    , m_previousStates{ std::exchange(other.m_previousStates, {}) }
{}

InputManager& InputManager::operator=(InputManager&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    m_window         = std::exchange(other.m_window, nullptr);
    m_currentStates  = std::exchange(other.m_currentStates, {});
    m_previousStates = std::exchange(other.m_previousStates, {});

    return *this;
}

void InputManager::update() {
    if (!m_window) {
        return;
    }

    m_previousStates = m_currentStates;

    m_currentStates[Key::A]      = glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS;
    m_currentStates[Key::D]      = glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS;
    m_currentStates[Key::Space]  = glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS;
    m_currentStates[Key::Escape] = glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}
