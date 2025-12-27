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

    [[nodiscard]] operator bool() const {
        return m_window != NULL;
    }

    [[nodiscard]] GLFWwindow* getNativeHandle() const {
        return m_window;
    }

    [[nodiscard]] std::pair<int, int> getFramebufferSize() const;
    [[nodiscard]] float getFramebufferAspectRatio() const;
    [[nodiscard]] bool shouldClose() const;

    void makeCurrentContext() const;
    void swapBuffers() const;
    void pollEvents() const;

    void setResizeCallback(const ResizeCallback& resizeCallback) {
        m_resizeCallback = resizeCallback;
    }

private:
    GLFWwindow* m_window{};
    ResizeCallback m_resizeCallback{};
};

#endif // WINDOW_H
