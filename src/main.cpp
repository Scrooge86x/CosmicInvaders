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

constexpr float initialWindowWidth{ 900.f };
constexpr float initialWindowHeight{ 600.f };

static float g_aspectRatio{ initialWindowWidth / initialWindowHeight};
static void framebufferSizeCallback(
    [[maybe_unused]] GLFWwindow* const window,
    const int width,
    const int height
) {
    glViewport(0, 0, width, height);
    if (height) {
        g_aspectRatio = static_cast<float>(width) / height;
    }
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
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    Vertex vertices[]{
        // back
        {{-0.5f, -0.5f, -0.5f}, {}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {}, {0.0f, 1.0f}},
        // front
        {{-0.5f, -0.5f,  0.5f}, {}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {}, {0.0f, 1.0f}},
        // left
        {{-0.5f, -0.5f, -0.5f}, {}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {}, {0.0f, 1.0f}},
        // right
        {{ 0.5f, -0.5f, -0.5f}, {}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {}, {0.0f, 1.0f}},
        // top
        {{-0.5f,  0.5f, -0.5f}, {}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {}, {0.0f, 1.0f}},
        // bottom
        {{-0.5f, -0.5f, -0.5f}, {}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {}, {0.0f, 1.0f}},
    };

    GLuint indices[]{
        // back
        0, 1, 2, 2, 3, 0,
        // front
        4, 5, 6, 6, 7, 4,
        // left
        8, 9,10,10,11, 8,
        // right
       12,13,14,14,15,12,
        // top
       16,17,18,18,19,16,
        // bottom
       20,21,22,22,23,20,
    };

    Mesh mesh{ vertices, indices, {
        .diffuse{ "assets/textures/texture.png" }
    } };
    Shader shader{ "assets/shaders/vertex-test.glsl", "assets/shaders/fragment-test.glsl" };

    glm::mat4 view{ glm::lookAt(
        glm::vec3{ 1.f, 1.f, 1.f },
        glm::vec3{ 0.f, 0.f, 0.f },
        glm::vec3{ 0.f, 1.f, 0.f }
    ) };

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float rotationSpeed{ 0.5f };
    float rotationAngle{};
    float modelScale{ 1.f };

    float lastTime{};
    while (!glfwWindowShouldClose(window)) {
        const float currentTime{ static_cast<float>(glfwGetTime()) };
        const float dt{ currentTime - lastTime };
        lastTime = currentTime;

        rotationAngle += dt * rotationSpeed;

        glClearColor(0.f, 0.5f, 0.5f, 1.f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection{ glm::perspective(glm::radians(90.0f), g_aspectRatio, 0.1f, 100.0f) };
        glm::mat4 model{ glm::rotate(glm::mat4{ 1.f }, rotationAngle, glm::vec3{ 0.5f, 1.f, 0.f }) };
        model = glm::scale(model, glm::vec3{ modelScale });

        const auto& [diffuse]{ mesh.getMaterial() };

        shader.use();
        shader.setMat4("u_model", model);
        shader.setMat4("u_view", view);
        shader.setMat4("u_projection", projection);

        diffuse.bind(0);
        shader.setInt("u_material.diffuse", 0);

        glBindVertexArray(mesh.getVao());
        glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, 0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Config");
        ImGui::SliderFloat("Rotation speed", &rotationSpeed, 0.5f, 5.f);
        ImGui::SliderFloat("Model scale", &modelScale, 0.01f, 30.f);
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
    glfwTerminate();
    return 0;
}
