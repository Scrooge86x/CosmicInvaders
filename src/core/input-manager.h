#pragma once

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <array>
#include <cstddef>

class InputManager {
public:
    enum Key {
        A,
        D,
        Space,
        Escape,
        KEY_COUNT,
    };

    void update(GLFWwindow* const window);

    bool isDown(const Key key) const { return m_currentStates[key]; }
    bool isHeld(const Key key) const { return m_currentStates[key] && m_previousStates[key]; }
    bool isPressed(const Key key) const { return m_currentStates[key] && !m_previousStates[key]; }

private:
    std::array<bool, Key::KEY_COUNT> m_currentStates{};
    std::array<bool, Key::KEY_COUNT> m_previousStates{};
};

#endif // INPUT_MANAGER_H
