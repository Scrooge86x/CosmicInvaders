#pragma once

#ifndef GUI_H
#define GUI_H

// This is included because ui-core will basically always be used together with imgui.h
#include <imgui.h>

struct GLFWwindow;

namespace ui {

void beginFrame();
void endFrame();

class ImGuiContextManager {
public:
    ImGuiContextManager(GLFWwindow* const window, const char* const glslVersion = "#version 330");
    ~ImGuiContextManager();

    ImGuiContextManager(const ImGuiContextManager&) = delete;
    ImGuiContextManager& operator=(const ImGuiContextManager&) = delete;

    ImGuiContextManager(ImGuiContextManager&&) = delete;
    ImGuiContextManager& operator=(ImGuiContextManager&&) = delete;

private:
    ImGuiContext* m_context{};
};

} // namespace ui

#endif // GUI_H
