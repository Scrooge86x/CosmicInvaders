#include <core/gl-window.h>
#include <gameplay/game.h>
#include <ui/ui-core.h>
#include <renderer/renderer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <format>
#include <iostream>

static int runGame() {
    GlWindow window{ 900, 600, "Cosmic Invaders", { 3, 3 } };
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        return -1;
    }

    Game game{ window };
    game.getCamera().setAspectRatio(window.getFramebufferAspectRatio());
    window.setResizeCallback([&game](const int width, const int height) {
        game.getCamera().setAspectRatio(static_cast<float>(width) / height);
    });

    ImGuiContextManager imGuiContext{ window.getNativeHandle(), "#version 330" };
    Renderer renderer{};
    Timer timer{};

    while (!window.shouldClose() && !game.shouldQuit()) {
        timer.update();

        window.pollEvents();

        ui::beginFrame();
        renderer.beginFrame(game.getLighting(), game.getCamera());

        game.update(timer.getDt<double>());
        game.render(renderer);

        renderer.endFrame();
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

    int returnValue{ -1 };
    try {
        returnValue = runGame();
    } catch (const std::exception& exception) {
        std::cerr << std::format("Fatal error: {}\n", exception.what());
    } catch (...) {
        std::cerr << "Unknown fatal error\n";
    }

    glfwTerminate();
    return returnValue;
}
