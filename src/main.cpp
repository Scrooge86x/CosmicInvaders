#include <iostream>

#include <core/gl-window.h>
#include <gameplay/game.h>
#include <ui/ui-core.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static int runGame() {
    GlWindow window{ 900, 600, "Cosmic Invaders", { 3, 3 } };
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        return -1;
    }

    ui::ImGuiContextManager imGuiContext{ window.getNativeHandle(), "#version 330" };

    Game game{};

    glEnable(GL_DEPTH_TEST); // TODO: Move to the Renderer class
    while (!window.shouldClose()) {
        glClearColor(0.f, 0.5f, 0.5f, 1.f); // TODO: Move to the Renderer class
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // TODO: Move to the Renderer class

        ui::beginFrame();
        ImGui::ShowDemoWindow();
        ui::endFrame();

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    int returnValue{ runGame() };

    glfwTerminate();
    return returnValue;
}
