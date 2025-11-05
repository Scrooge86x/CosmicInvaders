#include <iostream>
#include <filesystem>
#include <format>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
