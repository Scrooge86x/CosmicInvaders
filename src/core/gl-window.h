#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <utility>

class GlWindow {
public:
    using ResizeCallback = std::function<void(int, int)>;

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

    ~GlWindow() {
        glfwDestroyWindow(m_window);
    }

    operator bool() const {
        return m_window != NULL;
    }

    void makeCurrentContext() const;

    void setResizeCallback(const ResizeCallback& resizeCallback) {
        m_resizeCallback = resizeCallback;
    }

    std::pair<int, int> getFramebufferSize() const;

    float getFramebufferAspectRatio() const;

    GLFWwindow* getNativeHandle() const {
        return m_window;
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(m_window);
    }

    void swapBuffers() const {
        glfwSwapBuffers(m_window);
    }

    void pollEvents() const {
        glfwPollEvents();
    }

private:
    GLFWwindow* m_window{};
    ResizeCallback m_resizeCallback{};
};

#endif // WINDOW_H
