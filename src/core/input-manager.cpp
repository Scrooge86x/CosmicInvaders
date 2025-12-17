#include "input-manager.h"

void InputManager::update(GLFWwindow* const window) {
    m_previousStates = m_currentStates;

    m_currentStates[Key::A]      = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    m_currentStates[Key::D]      = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    m_currentStates[Key::Space]  = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    m_currentStates[Key::Escape] = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}
