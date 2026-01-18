#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <utility>

struct GLFWwindow;

/**
 * @brief RAII wrapper around a GLFW window and OpenGL context.
 *
 * Manages window creation, context handling, buffer swapping
 * and event polling.
 */
class GlWindow {
public:
    using ResizeCallback = std::function<void(int, int)>;

    /**
     * @brief Creates a window and OpenGL context.
     *
     * @throws std::runtime_error If the window cannot be created or
     *         OpenGL initialization fails.
     */
    GlWindow(
        const int width,
        const int height,
        const char* const title,
        const std::pair<int, int> openGlVersion = { 3, 3 }
    );

    GlWindow(const GlWindow&) = delete;
    GlWindow& operator=(const GlWindow&) = delete;

    GlWindow(GlWindow&& other) noexcept;
    GlWindow& operator=(GlWindow&& other) noexcept;

    /**
     * @brief Destroys the window.
     */
    ~GlWindow();

    /**
     * @brief Returns the native GLFW window handle.
     */
    [[nodiscard]] GLFWwindow* getNativeHandle() const {
        return m_window;
    }

    /**
     * @brief Returns the framebuffer size in pixels.
     */
    [[nodiscard]] std::pair<int, int> getFramebufferSize() const;

    /**
     * @brief Calculates the current framebuffer aspect ratio.
     *
     * Helper method useful for calculating projection matrix
     */
    [[nodiscard]] float getFramebufferAspectRatio() const;

    /**
     * @brief Checks if the window should close (for example if the user pressed the X button on the titlebar).
     */
    [[nodiscard]] bool shouldClose() const;

    /**
     * @brief Makes this window's context current.
     */
    void makeCurrentContext() const;

    /**
     * @brief Swaps front and back buffers.
     */
    void swapBuffers() const;

    /**
     * @brief Polls window events.
     */
    void pollEvents() const;

    /**
     * @brief Sets a callback invoked on window resize.
     */
    void setResizeCallback(const ResizeCallback& resizeCallback) {
        m_resizeCallback = resizeCallback;
    }

private:
    GLFWwindow* m_window{};
    ResizeCallback m_resizeCallback{};
};

#endif // WINDOW_H
