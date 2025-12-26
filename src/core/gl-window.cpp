#include "gl-window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GlWindow::GlWindow(
    const int width,
    const int height,
    const char* const title,
    const std::pair<int, int> openGlVersion
) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGlVersion.first);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGlVersion.second);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_window) {
        return;
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        if (glfwGetCurrentContext() == window) {
            glViewport(0, 0, width, height);
        }

        GlWindow* thisWindow{ static_cast<GlWindow*>(glfwGetWindowUserPointer(window)) };
        if (thisWindow) {
            thisWindow->m_resizeCallback(width, height);
        }
    });
}

GlWindow::GlWindow(GlWindow&& other) noexcept
    : m_window        { std::exchange(other.m_window, nullptr) }
    , m_resizeCallback{ std::exchange(other.m_resizeCallback, {}) } {}

GlWindow& GlWindow::operator=(GlWindow&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    glfwDestroyWindow(m_window);

    m_window         = std::exchange(other.m_window, nullptr);
    m_resizeCallback = std::exchange(other.m_resizeCallback, {});

    return *this;
}

GlWindow::~GlWindow() {
    glfwDestroyWindow(m_window);
}

std::pair<int, int> GlWindow::getFramebufferSize() const {
    int width{};
    int height{};
    glfwGetFramebufferSize(m_window, &width, &height);
    return { width, height };
}

float GlWindow::getFramebufferAspectRatio() const {
    const auto& [width, height] { getFramebufferSize() };
    return static_cast<float>(width) / height;
}

void GlWindow::makeCurrentContext() const {
    glfwMakeContextCurrent(m_window);

    const auto& [width, height] { getFramebufferSize() };
    if (glViewport) {
        glViewport(0, 0, width, height);
    }
}

bool GlWindow::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void GlWindow::swapBuffers() const {
    glfwSwapBuffers(m_window);
}

void GlWindow::pollEvents() const {
    glfwPollEvents();
}
