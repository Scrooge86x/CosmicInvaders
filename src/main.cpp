#include <iostream>
#include <filesystem>
#include <format>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "renderer/shader.h"

static void framebufferSizeCallback(
    [[maybe_unused]] GLFWwindow* const window,
    const int width,
    const int height
) {
    glViewport(0, 0, width, height);
}

int main() {
    glm::mat2 matrix1{ 1.f, 2.f,
                       2.f, 1.f };
    glm::mat2 matrix2{ 2.f, 1.f,
                       1.f, 2.f };
    glm::mat2 matrix3{ matrix1 * matrix2 };
    std::cout << std::format("[{}, {}]\n[{}, {}]\n", matrix3[0][0], matrix3[0][1], matrix3[1][0], matrix3[1][1]);

    if (!std::filesystem::exists("assets/textures/texture.png")) {
        std::cerr << "Failed to read assets\n";
        return -1;
    }

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

    GLFWwindow* window{ glfwCreateWindow(900, 600, "Test Window", NULL, NULL) };
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    Shader shader{ "assets/shaders/vertex-test.glsl", "assets/shaders/fragment-test.glsl" };

    float vertices[]{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    GLuint VBO{};
    GLuint VAO{};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        const float currentTime{ static_cast<float>(glfwGetTime()) };
        shader.setVec3("color", 0.0f, 0.0f, (sin(currentTime * 2.f) / 2.f) + .5f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    ma_engine_uninit(&audioEngine);
    glfwTerminate();
    return 0;
}
