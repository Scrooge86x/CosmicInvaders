#pragma once

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <array>
#include <cstddef>

struct GLFWwindow;

class InputManager {
public:
    enum Key {
        A,
        D,
        Space,
        Escape,
        KEY_COUNT,
    };

    explicit InputManager(GLFWwindow* const window);

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    InputManager(InputManager&& other) noexcept;
    InputManager& operator=(InputManager&& other) noexcept;

    void update();

    bool isDown(const Key key) const { return m_currentStates[key]; }
    bool isHeld(const Key key) const { return m_currentStates[key] && m_previousStates[key]; }
    bool isPressed(const Key key) const { return m_currentStates[key] && !m_previousStates[key]; }

private:
    GLFWwindow* m_window{};
    std::array<bool, Key::KEY_COUNT> m_currentStates{};
    std::array<bool, Key::KEY_COUNT> m_previousStates{};
};

#endif // INPUT_MANAGER_H
