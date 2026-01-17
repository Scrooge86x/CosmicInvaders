#include <core/gl-window.h>
#include <core/fps-counter.h>
#include <core/input-manager.h>
#include <core/settings.h>
#include <core/audio-engine.h>
#include <core/timer.h>

#include <renderer/shader.h>
#include <renderer/material.h>
#include <renderer/model.h>
#include <renderer/model-store.h>
#include <renderer/lighting.h>
#include <renderer/camera.h>
#include <renderer/renderer.h>

#include <ui/ui-core.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

static int runDemo() {
    AudioEngine audioEngine{};
    audioEngine.play("assets/sounds/space-laser.mp3");

    GlWindow window{ 900, 600, "Cosmic Invaders", { 3, 3 } };
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        return -1;
    }

    Camera camera{ { 0.f, 0.f, 1.f } };
    camera.setAspectRatio(window.getFramebufferAspectRatio());
    window.setResizeCallback([&camera, &window](int, int) {
        camera.setAspectRatio(window.getFramebufferAspectRatio());
    });

    ModelStore modelStore{};
    constexpr auto objectPath{ "assets/3d-models/Battle-SpaceShip-Free-3D-Low-Poly-Models/Destroyer_01.fbx" };
    const auto object{ modelStore.load(objectPath, 0.0003f) };
    if (object != modelStore.load(objectPath, 0.0003f)) {
        std::cerr << "ModelStore failed to cache the object!\n";
        return -1;
    }
    if (object == modelStore.load(objectPath, 1.f)) {
        std::cerr << "ModelStore cached differently scaled objects!\n";
        return -1;
    }

    FpsCounter fpsCounter{};
    InputManager inputManager{ window.getNativeHandle() };
    Settings settings{ "config.json" };
    Timer timer{};
    Renderer renderer{};

    bool isGuiVisible{ true };
    float modelScale{ 3.f };
    float rotationSpeed{ 0.5f };
    float rotationAngle{};
    glm::vec3 position{ 0.f, -2.f, -10.f };
    Lighting lighting{
        .sunPosition{ 0.f, 20.f, 0.f },
        .sunColor{ 1.f, 1.f, 3.f },
    };

    ImGuiContextManager imGuiContext{ window.getNativeHandle(), "#version 330" };

    while (!window.shouldClose()) {
        timer.update();

        rotationAngle += timer.getDt<float>() * rotationSpeed;

        fpsCounter.update(timer.getDt<double>());
        inputManager.update();

        glm::mat4 model{ 1.f };
        model = glm::translate(model, position);
        model = glm::rotate(model, rotationAngle, glm::vec3{ 0.5f, 1.f, 0.f });
        model = glm::scale(model, glm::vec3{ modelScale });

        renderer.beginFrame(lighting, camera);
        renderer.draw(*object, model);
        renderer.endFrame();

        ui::beginFrame();

        ImGui::ShowDemoWindow();

        if (inputManager.isPressed(InputManager::Key::Escape)) {
            isGuiVisible = !isGuiVisible;
        }
        if (isGuiVisible) {
            ImGui::Begin("Config (Press ESC to close)", &isGuiVisible);
            if (settings.showFps) {
                ImGui::Text("Fps %lf", fpsCounter.getFps());
            }
            ImGui::Checkbox("Show fps", &settings.showFps);
            ImGui::SliderFloat("Rotation speed", &rotationSpeed, 0.5f, 5.f);
            ImGui::SliderFloat("Model scale", &modelScale, 0.01f, 30.f);
            ImGui::SliderFloat3("Model position", &position[0], -20.f, 20.f);
            ImGui::SliderFloat3("Ambient light", &lighting.ambient[0], 0.f, 1.5f);
            ImGui::SliderFloat3("Sun position", &lighting.sunPosition[0], -20.f, 20.f);
            ImGui::SliderFloat3("Sun color", &lighting.sunColor[0], 0.f, 5.f);
            if (ImGui::Button("Save config")) {
                settings.saveToFile();
            }
            ImGui::End();
        }

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

    int returnValue{ runDemo() };

    glfwTerminate();
    return returnValue;
}
