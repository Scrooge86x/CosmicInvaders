#include <iostream>
#include <filesystem>
#include <format>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/gl-window.h"
#include "core/fps-counter.h"
#include "core/input-manager.h"
#include "core/model-store.h"
#include "core/settings.h"
#include "core/audio-engine.h"

#include "renderer/shader.h"
#include "renderer/texture2d.h"
#include "renderer/material.h"
#include "renderer/model.h"
#include "renderer/lighting.h"
#include "renderer/camera.h"

#include "ui/ui-core.h"

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

    window.makeCurrentContext();
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    ModelStore modelStore{};
    const auto object{ modelStore.load("assets/3d-models/DiffuseTransmissionPlant.glb", 2.f) };
    if (object != modelStore.load("assets/3d-models/DiffuseTransmissionPlant.glb", 2.f)) {
        std::cerr << "ModelStore failed to cache the object!\n";
        return -1;
    }
    if (object == modelStore.load("assets/3d-models/DiffuseTransmissionPlant.glb", 1.f)) {
        std::cerr << "ModelStore cached differently scaled objects!\n";
        return -1;
    }

    Shader shader{ "assets/shaders/vertex-test.glsl", "assets/shaders/fragment-test.glsl" };
    FpsCounter fpsCounter{};
    InputManager inputManager{};
    Settings settings{ "config.json" };

    bool isGuiVisible{ true };
    float rotationAngle{};
    glm::vec3 position{ 0.f, -2.f, -10.f };
    Lighting lighting{
        .sunPosition{ 0.f, -20.f, 0.f },
        .sunColor{ 1.f, 1.f, 3.f },
    };

    float previousTime{};
    glEnable(GL_DEPTH_TEST);

    ui::ImGuiContextManager imGuiContext{ window.getNativeHandle(), "#version 330" };

    while (!window.shouldClose()) {
        const float currentTime{ static_cast<float>(glfwGetTime()) };
        const float dt{ currentTime - previousTime };
        previousTime = currentTime;

        rotationAngle += dt * settings.rotationSpeed;

        fpsCounter.update(dt);
        inputManager.update(window.getNativeHandle());

        glClearColor(0.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model{ 1.f };
        model = glm::translate(model, position);
        model = glm::rotate(model, rotationAngle, glm::vec3{ 0.5f, 1.f, 0.f });
        model = glm::scale(model, glm::vec3{ settings.modelScale });
        glm::mat3 normal{ glm::transpose(glm::inverse(glm::mat3{ model })) };

        shader.use();
        shader.setMat4("u_mvp", camera.getViewProjection() * model);
        shader.setMat3("u_normal", normal);
        shader.setVec3("u_lighting.ambient", lighting.ambient);
        shader.setVec3("u_lighting.sunPosition", lighting.sunPosition);
        shader.setVec3("u_lighting.sunColor", lighting.sunColor);
        shader.setVec3("u_cameraPos", camera.getPosition());

        for (const auto& mesh : object->getMeshes()) {
            const auto& material{ *mesh.getMaterial() };
            if (material.diffuse) {
                material.diffuse->bind(0);
                shader.setInt("u_material.diffuse", 0);
            }
            shader.setVec3("u_material.specularColor", material.specularColor);
            shader.setFloat("u_material.specularStrength", material.specularStrength);
            shader.setFloat("u_material.shininess", material.shininess);

            glBindVertexArray(mesh.getVao());
            glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, NULL);
        }

        ui::beginFrame();

        ImGui::ShowDemoWindow();

        if (inputManager.isPressed(InputManager::Key::Escape)) {
            isGuiVisible = !isGuiVisible;
        }
        if (isGuiVisible) {
            ImGui::Begin("Config (Press ESC to close)", &isGuiVisible);
            ImGui::Text("Fps %lf", fpsCounter.getFps());
            ImGui::SliderFloat("Rotation speed", &settings.rotationSpeed, 0.5f, 5.f);
            ImGui::SliderFloat("Model scale", &settings.modelScale, 0.01f, 30.f);
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
