#include <iostream>
#include <filesystem>
#include <format>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <miniaudio.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "renderer/shader.h"
#include "renderer/texture2d.h"
#include "renderer/mesh.h"
#include "renderer/model.h"

int main() {
    ma_engine audioEngine{};
    if (ma_engine_init(NULL, &audioEngine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize miniaudio engine\n";
        return -1;
    }

    ma_engine_play_sound(&audioEngine, "assets/sounds/space-laser.mp3", NULL);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    constexpr float initialWindowWidth{ 900.f };
    constexpr float initialWindowHeight{ 600.f };

    GLFWwindow* window{ glfwCreateWindow(
        static_cast<int>(initialWindowWidth),
        static_cast<int>(initialWindowHeight),
        "Test Window",
        NULL,
        NULL
    ) };
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glm::mat4 view{ glm::lookAt(
        glm::vec3{ 0.f, 0.f, 1.f },
        glm::vec3{ 0.f, 0.f, 0.f },
        glm::vec3{ 0.f, 1.f, 0.f }
    ) };

    static glm::mat4 projection{ glm::perspective(glm::radians(90.0f), initialWindowWidth / initialWindowHeight, 0.1f, 100.0f) };
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, const int width, const int height) {
        glViewport(0, 0, width, height);
        if (height) {
            projection = glm::perspective(glm::radians(90.0f), static_cast<float>(width) / height, 0.1f, 100.0f);
        }
    });

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    Model object{ "assets/3d-models/DiffuseTransmissionPlant.glb", glm::scale(glm::mat4{ 1.f }, glm::vec3{ 2.f, 2.f, 2.f }) };
    Shader shader{ "assets/shaders/vertex-test.glsl", "assets/shaders/fragment-test.glsl" };

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float rotationSpeed{ 0.5f };
    float rotationAngle{};
    float modelScale{ 4.f };
    glm::vec3 position{ 0.f, -2.f, -5.f };

    glEnable(GL_DEPTH_TEST);
    float previousTime{};

    while (!glfwWindowShouldClose(window)) {
        const float currentTime{ static_cast<float>(glfwGetTime()) };
        const float dt{ currentTime - previousTime };
        previousTime = currentTime;

        rotationAngle += dt * rotationSpeed;

        glClearColor(0.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model{ 1.f };
        model = glm::translate(model, position);
        model = glm::rotate(model, rotationAngle, glm::vec3{ 0.5f, 1.f, 0.f });
        model = glm::scale(model, glm::vec3{ modelScale });

        shader.use();
        shader.setMat4("u_mvp", projection * view * model);

        for (const auto& mesh : object.getMeshes()) {
            const auto& [diffuse] { *mesh.getMaterial() };
            if (diffuse) {
                diffuse->bind(0);
                shader.setInt("u_material.diffuse", 0);
            }

            glBindVertexArray(mesh.getVao());
            glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, NULL);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Config");
        ImGui::SliderFloat("Rotation speed", &rotationSpeed, 0.5f, 5.f);
        ImGui::SliderFloat("Model scale", &modelScale, 0.01f, 30.f);
        ImGui::SliderFloat("Position X", &position.x, -10.f, 10.f);
        ImGui::SliderFloat("Position Y", &position.y, -10.f, 10.f);
        ImGui::SliderFloat("Position Z", &position.z, -15.f, -0.5f);
        ImGui::End();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    ma_engine_uninit(&audioEngine);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
