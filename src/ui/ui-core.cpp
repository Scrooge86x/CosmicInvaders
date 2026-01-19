#include "ui-core.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <stdexcept>

namespace ui {

void beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace ui

ImGuiContextManager::ImGuiContextManager(GLFWwindow* const window, const char* const glslVersion) {
    if (ImGui::GetCurrentContext()) {
        throw std::runtime_error{ "ImGui context already exists" };
    }

    IMGUI_CHECKVERSION();
    m_context = ImGui::CreateContext();

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        ImGui::DestroyContext(m_context);
        throw std::runtime_error{ "Failed to initialize ImGui GLFW backend" };
    }
    if (!ImGui_ImplOpenGL3_Init(glslVersion)) {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext(m_context);
        throw std::runtime_error{ "Failed to initialize ImGui OpenGL3 backend" };
    }
}

ImGuiContextManager::~ImGuiContextManager() {
    if (!m_context) {
        return;
    }

    ImGui::SetCurrentContext(m_context);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(m_context);
    m_context = nullptr;
}
