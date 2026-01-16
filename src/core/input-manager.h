#pragma once

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <array>
#include <cstddef>

struct GLFWwindow;

/**
 * @brief Handles keyboard input state tracking.
 *
 * Tracks current and previous key states
 * to detect presses and holds.
 */
class InputManager {
public:
    enum Key {
        A,
        D,
        Space,
        Escape,
        KEY_COUNT,
    };

    /**
     * @brief Constructs the input manager.
     * @param window GLFW window to read input from.
     */
    explicit InputManager(GLFWwindow* const window);

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    InputManager(InputManager&& other) noexcept;
    InputManager& operator=(InputManager&& other) noexcept;

    /**
     * @brief Updates input states.
     *
     * Should be called once per frame.
     */
    void update();

    /**
     * @brief Checks if a key was down during the latest update.
     */
    [[nodiscard]] bool isDown(const Key key) const { return m_currentStates[key]; }

    /**
     * @brief Checks if a was down during both previous and latest updates.
     */
    [[nodiscard]] bool isHeld(const Key key) const { return m_currentStates[key] && m_previousStates[key]; }

    /**
     * @brief Checks if a key was pressed this frame (up in the previous update and down in the latest one).
     */
    [[nodiscard]] bool isPressed(const Key key) const { return m_currentStates[key] && !m_previousStates[key]; }

private:
    GLFWwindow* m_window{};
    std::array<bool, Key::KEY_COUNT> m_currentStates{};
    std::array<bool, Key::KEY_COUNT> m_previousStates{};
};

#endif // INPUT_MANAGER_H
