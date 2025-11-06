#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <filesystem>

class Shader {
public:
    using GLCharString = std::basic_string<GLchar>;

    Shader(
        const std::filesystem::path& vertexShaderPath,
        const std::filesystem::path& fragmentShaderPath,
        const std::filesystem::path& geometryShaderPath = {}
    );

    ~Shader() {
        deleteShaderProgram();
    }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    bool reload();

    void use() const {
        glUseProgram(m_shaderProgramId);
    }

    [[nodiscard]] GLuint getId() const {
        return m_shaderProgramId;
    }

    void setBool(const GLchar* const name, const bool value) const {
        glUniform1i(glGetUniformLocation(m_shaderProgramId, name), static_cast<int>(value));
    }

    void setInt(const GLchar* const name, const int value) const {
        glUniform1i(glGetUniformLocation(m_shaderProgramId, name), value);
    }

    void setFloat(const GLchar* const name, const float value) const {
        glUniform1f(glGetUniformLocation(m_shaderProgramId, name), value);
    }

    void setVec2(const GLchar* const name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(m_shaderProgramId, name), 1, &value[0]);
    }

    void setVec2(const GLchar* const name, const float x, const float y) const {
        glUniform2f(glGetUniformLocation(m_shaderProgramId, name), x, y);
    }

    void setVec3(const GLchar* const name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(m_shaderProgramId, name), 1, &value[0]);
    }

    void setVec3(const GLchar* const name, const float x, const float y, const float z) const {
        glUniform3f(glGetUniformLocation(m_shaderProgramId, name), x, y, z);
    }

    void setVec4(const GLchar* const name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(m_shaderProgramId, name), 1, &value[0]);
    }

    void setVec4(const GLchar* const name, const float x, const float y, const float z, const float w) const {
        glUniform4f(glGetUniformLocation(m_shaderProgramId, name), x, y, z, w);
    }

    void setMat2(const GLchar* const name, const glm::mat2& mat) const {
        glUniformMatrix2fv(glGetUniformLocation(m_shaderProgramId, name), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const GLchar* const name, const glm::mat3& mat) const {
        glUniformMatrix3fv(glGetUniformLocation(m_shaderProgramId, name), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const GLchar* const name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramId, name), 1, GL_FALSE, &mat[0][0]);
    }

private:
    GLuint createShaderFromFile(const GLenum type, const std::filesystem::path& fileName);

    void deleteShaderProgram();
    void createShaderProgram();

    GLuint m_shaderProgramId{};
    std::filesystem::path m_vertexShaderPath{};
    std::filesystem::path m_fragmentShaderPath{};
    std::filesystem::path m_geometryShaderPath{};
};

#endif // SHADER_H
