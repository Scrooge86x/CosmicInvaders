#include <core/gl-window.h>
#include <gameplay/game.h>
#include <ui/ui-core.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

static int runGame() {
    GlWindow window{ 900, 600, "Cosmic Invaders", { 3, 3 } };
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        return -1;
    }

    ui::ImGuiContextManager imGuiContext{ window.getNativeHandle(), "#version 330" };
    Timer timer{};

    InputManager inputManager{ window.getNativeHandle() };
    Game game{ inputManager };

    game.getCamera().setAspectRatio(window.getFramebufferAspectRatio());
    window.setResizeCallback([&game](const int width, const int height) {
        game.getCamera().setAspectRatio(static_cast<float>(width) / height);
    });

    glEnable(GL_DEPTH_TEST); // TODO: Move to the Renderer class
    while (!window.shouldClose() && !game.shouldQuit()) {
        timer.update();

        window.pollEvents();
        inputManager.update();

        glClearColor(0.05f, 0.05f, 0.05f, 1.f); // TODO: Move to the Renderer class
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // TODO: Move to the Renderer class

        ui::beginFrame();
        game.update(timer.getDt<double>());
        ui::endFrame();

        window.swapBuffers();
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
