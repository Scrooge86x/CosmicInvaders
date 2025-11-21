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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "renderer/shader.h"
#include "renderer/texture2d.h"
#include "renderer/mesh.h"

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
        glm::vec3{ 1.f, 1.f, 1.f },
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

    Assimp::Importer importer{};
    const aiScene* scene{ importer.ReadFile(
        "assets/3d-models/Avocado.glb",
        aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs
    ) };

    if (!scene) {
        std::cerr << importer.GetErrorString() << '\n';
        return -1;
    }
    if (scene->mNumMeshes != 1) {
        std::cerr << "Demo expects only one mesh in a file.\n";
        return -1;
    }

    auto material{ std::make_shared<Material>() };
    aiMesh* assimpMesh{ scene->mMeshes[0] };

    aiMaterial* assimpMaterial{ scene->mMaterials[assimpMesh->mMaterialIndex] };
    if (assimpMaterial->GetTextureCount(aiTextureType_DIFFUSE)) {
        aiString texturePath{};
        assimpMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
        if (texturePath.C_Str()[0] == '*') {
            material->diffuse = Texture2D{ *scene->mTextures[std::atoi(texturePath.C_Str() + 1)] };
        } else {
            material->diffuse = Texture2D{ texturePath.C_Str() };
        }
    }

    Mesh mesh{ *assimpMesh, material };
    Shader shader{ "assets/shaders/vertex-test.glsl", "assets/shaders/fragment-test.glsl" };

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float rotationSpeed{ 0.5f };
    float rotationAngle{};
    float modelScale{ 20.f };
    float lastTime{};

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        const float currentTime{ static_cast<float>(glfwGetTime()) };
        const float dt{ currentTime - lastTime };
        lastTime = currentTime;

        rotationAngle += dt * rotationSpeed;

        glClearColor(0.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model{ glm::rotate(glm::mat4{ 1.f }, rotationAngle, glm::vec3{ 0.5f, 1.f, 0.f }) };
        model = glm::scale(model, glm::vec3{ modelScale });

        shader.use();
        shader.setMat4("u_model", model);
        shader.setMat4("u_view", view);
        shader.setMat4("u_projection", projection);

        const auto& [diffuse]{ *mesh.getMaterial() };
        if (diffuse) {
            diffuse->bind(0);
            shader.setInt("u_material.diffuse", 0);
        }

        glBindVertexArray(mesh.getVao());
        glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, NULL);

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
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
