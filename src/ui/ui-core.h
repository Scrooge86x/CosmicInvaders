#pragma once

#ifndef GUI_H
#define GUI_H

// This is included because ui-core will basically always be used together with imgui.h
#include <imgui.h>

struct GLFWwindow;

namespace ui {

/**
 * @brief Begins a new ImGui frame.
 *
 * Must be called once per frame before issuing any ImGui draw calls.
 * Assumes a valid ImGui context and initialized GLFW and OpenGL backends.
 */
void beginFrame();

/**
 * @brief Ends the current ImGui frame and renders it.
 *
 * Must be called once per frame after all ImGui draw calls.
 * Submits draw data to the OpenGL backend.
 * Assumes a valid ImGui context and initialized GLFW and OpenGL backends.
 */
void endFrame();

} // namespace ui

/**
 * @class ImGuiContextManager
 * @brief RAII manager for ImGui context and backend lifetime.
 *
 * Creates and owns the global ImGui context and initializes
 * the GLFW and OpenGL3 backends.
 *
 * Enforces a single active ImGui context per application.
 * Construction fails if a context already exists.
 *
 * The destructor shuts down all ImGui backends and destroys
 * the associated context.
 */
class ImGuiContextManager {
public:
    /**
     * @brief Creates the ImGui context and initializes backends.
     *
     * Requires a valid GLFW window and active OpenGL context.
     *
     * @param window GLFW window used by ImGui.
     * @param glslVersion GLSL version string (e.g. "#version 330").
     *
     * @throws std::runtime_error If an ImGui context already exists.
     */
    ImGuiContextManager(GLFWwindow* const window, const char* const glslVersion = "#version 330");

    /**
     * @brief Shuts down ImGui backends and destroys the context.
     *
     * Safe to call even if context creation failed.
     */
    ~ImGuiContextManager();

    ImGuiContextManager(const ImGuiContextManager&) = delete;
    ImGuiContextManager& operator=(const ImGuiContextManager&) = delete;

    ImGuiContextManager(ImGuiContextManager&&) = delete;
    ImGuiContextManager& operator=(ImGuiContextManager&&) = delete;

private:
    ImGuiContext* m_context{};
};

#endif // GUI_H
