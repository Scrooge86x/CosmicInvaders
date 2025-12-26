#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <utility>

struct GLFWwindow;

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

    ~GlWindow();

    operator bool() const {
        return m_window != NULL;
    }

    void setResizeCallback(const ResizeCallback& resizeCallback) {
        m_resizeCallback = resizeCallback;
    }

    GLFWwindow* getNativeHandle() const {
        return m_window;
    }

    std::pair<int, int> getFramebufferSize() const;
    float getFramebufferAspectRatio() const;

    void makeCurrentContext() const;
    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;

private:
    GLFWwindow* m_window{};
    ResizeCallback m_resizeCallback{};
};

#endif // WINDOW_H
