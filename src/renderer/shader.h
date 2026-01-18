#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <filesystem>
#include <unordered_map>

/**
 * @brief OpenGL shader program wrapper.
 *
 * Compiles, links and manages a shader program
 * and uniform access.
 */
class Shader {
public:
    using GLCharString = std::basic_string<GLchar>;

    /**
     * @brief Creates a shader program from source files.
     *
     * @throws std::runtime_error
     * If the specified files cannot be opened or the shader linking/compilation fails.
     */
    Shader(
        const std::filesystem::path& vertexShaderPath,
        const std::filesystem::path& fragmentShaderPath,
        const std::filesystem::path& geometryShaderPath = {}
    );

    /**
     * @brief Destroys the shader program.
     */
    ~Shader() {
        deleteShaderProgram();
    }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    /**
     * @brief Activates the shader program.
     */
    void use() const {
        glUseProgram(m_shaderProgramId);
    }

    /**
     * @brief Returns the OpenGL program ID.
     */
    [[nodiscard]] GLuint getId() const {
        return m_shaderProgramId;
    }

    /**
     * @brief Returns cached uniform location for a given name.
     */
    [[nodiscard]] GLint getUniformLocation(const GLchar* const name);

    void setBool(const GLchar* const name, const bool value) {
        glUniform1i(getUniformLocation(name), static_cast<int>(value));
    }

    void setInt(const GLchar* const name, const int value) {
        glUniform1i(getUniformLocation(name), value);
    }

    void setFloat(const GLchar* const name, const float value) {
        glUniform1f(getUniformLocation(name), value);
    }

    void setVec2(const GLchar* const name, const glm::vec2& value) {
        glUniform2fv(getUniformLocation(name), 1, &value[0]);
    }

    void setVec2(const GLchar* const name, const float x, const float y) {
        glUniform2f(getUniformLocation(name), x, y);
    }

    void setVec3(const GLchar* const name, const glm::vec3& value) {
        glUniform3fv(getUniformLocation(name), 1, &value[0]);
    }

    void setVec3(const GLchar* const name, const float x, const float y, const float z) {
        glUniform3f(getUniformLocation(name), x, y, z);
    }

    void setVec4(const GLchar* const name, const glm::vec4& value) {
        glUniform4fv(getUniformLocation(name), 1, &value[0]);
    }

    void setVec4(const GLchar* const name, const float x, const float y, const float z, const float w) {
        glUniform4f(getUniformLocation(name), x, y, z, w);
    }

    void setMat2(const GLchar* const name, const glm::mat2& mat) {
        glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const GLchar* const name, const glm::mat3& mat) {
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const GLchar* const name, const glm::mat4& mat) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
    }

private:
    GLuint createShaderFromFile(const GLenum type, const std::filesystem::path& fileName);

    void deleteShaderProgram();
    void createShaderProgram();

    GLuint m_shaderProgramId{};
    std::filesystem::path m_vertexShaderPath{};
    std::filesystem::path m_fragmentShaderPath{};
    std::filesystem::path m_geometryShaderPath{};
    std::unordered_map<GLCharString, GLint> m_uniformLocations{};
};

#endif // SHADER_H
