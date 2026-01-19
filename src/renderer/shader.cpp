#include "shader.h"

#include "gl-call.h"

#include <fstream>
#include <iostream>
#include <utility>

Shader::Shader(
    const std::filesystem::path& vertexShaderPath,
    const std::filesystem::path& fragmentShaderPath,
    const std::filesystem::path& geometryShaderPath)
        : m_vertexShaderPath  { vertexShaderPath }
        , m_fragmentShaderPath{ fragmentShaderPath }
        , m_geometryShaderPath{ geometryShaderPath } {
    try {
        createShaderProgram();
    } catch (...) {
        deleteShaderProgram();
        throw;
    }
}

Shader::Shader(Shader&& other) noexcept
    : m_shaderProgramId   { std::exchange(other.m_shaderProgramId, 0) }
    , m_vertexShaderPath  { std::move(other.m_vertexShaderPath) }
    , m_fragmentShaderPath{ std::move(other.m_fragmentShaderPath) }
    , m_geometryShaderPath{ std::move(other.m_geometryShaderPath) }
    , m_uniformLocations  { std::move(other.m_uniformLocations) }
{}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    deleteShaderProgram();

    m_shaderProgramId    = std::exchange(other.m_shaderProgramId, 0);
    m_vertexShaderPath   = std::move(other.m_vertexShaderPath);
    m_fragmentShaderPath = std::move(other.m_fragmentShaderPath);
    m_geometryShaderPath = std::move(other.m_geometryShaderPath);
    m_uniformLocations   = std::move(other.m_uniformLocations);

    return *this;
}

GLint Shader::getUniformLocation(const GLchar* const name) {
    auto [it, wasInserted]{ m_uniformLocations.try_emplace(name, 0) };
    return !wasInserted ? it->second : (it->second = glGetUniformLocation(m_shaderProgramId, name));
}

GLuint Shader::createShaderFromFile(const GLenum type, const std::filesystem::path& fileName) {
    std::ifstream shaderFile{ fileName };
    if (!shaderFile) {
        throw std::runtime_error{ std::format("Failed to open shader file: {}", fileName.generic_string()) };
    }

    const GLCharString shaderSource{
        std::istreambuf_iterator<GLchar>{ shaderFile },
        std::istreambuf_iterator<GLchar>{}
    };
    const GLchar* const sourcePtr{ shaderSource.c_str() };

    const GLuint shader{ glCreateShader(type) };
    if (!shader) {
        throw std::runtime_error{ "glCreateShader failed" };
    }

    glShaderSource(shader, 1, &sourcePtr, NULL);
    glCompileShader(shader);

    GLint success{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) {
        return shader;
    }

    GLint infoLogSize{};
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogSize);

    GLCharString infoLog{};
    infoLog.resize(infoLogSize);
    glGetShaderInfoLog(shader, infoLogSize, NULL, infoLog.data());

    glDeleteShader(shader);
    throw std::runtime_error{ std::format(R"(Shader compilation of "{}" failed: {})",
        fileName.generic_string(),
        infoLog
    ) };
}

void Shader::deleteShaderProgram() noexcept {
    if (m_shaderProgramId) {
        glDeleteProgram(m_shaderProgramId);
        m_shaderProgramId = 0;
    }
}

void Shader::createShaderProgram() {
    deleteShaderProgram();

    m_shaderProgramId = glCreateProgram();
    if (!m_shaderProgramId) {
        throw std::runtime_error{ "glCreateProgram failed" };
    }

    const GLuint vertexShader{ createShaderFromFile(GL_VERTEX_SHADER, m_vertexShaderPath) };
    glAttachShader(m_shaderProgramId, vertexShader);
    glDeleteShader(vertexShader);

    const GLuint fragmentShader{ createShaderFromFile(GL_FRAGMENT_SHADER, m_fragmentShaderPath) };
    glAttachShader(m_shaderProgramId, fragmentShader);
    glDeleteShader(fragmentShader);

    if (!m_geometryShaderPath.empty()) {
        const GLuint geometryShader{ createShaderFromFile(GL_GEOMETRY_SHADER, m_geometryShaderPath) };
        glAttachShader(m_shaderProgramId, geometryShader);
        glDeleteShader(geometryShader);
    }

    glLinkProgram(m_shaderProgramId);

    GLint success{};
    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
    if (success) {
        return;
    }

    GLint infoLogSize{};
    glGetProgramiv(m_shaderProgramId, GL_INFO_LOG_LENGTH, &infoLogSize);

    GLCharString infoLog{};
    infoLog.resize(infoLogSize);
    glGetProgramInfoLog(m_shaderProgramId, infoLogSize, NULL, infoLog.data());

    throw std::runtime_error{ std::format("Program linking failed: {}", infoLog) };
}

