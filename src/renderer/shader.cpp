#include "shader.h"

#include <utility>
#include <iostream>
#include <fstream>

Shader::Shader(
    const std::filesystem::path& vertexShaderPath,
    const std::filesystem::path& fragmentShaderPath,
    const std::filesystem::path& geometryShaderPath)
        : m_vertexShaderPath  { vertexShaderPath }
        , m_fragmentShaderPath{ fragmentShaderPath }
        , m_geometryShaderPath{ geometryShaderPath } {
    createShaderProgram();
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

bool Shader::reload() {
    deleteShaderProgram();
    createShaderProgram();
    return m_shaderProgramId != 0;
}

GLint Shader::getUniformLocation(const GLchar* const name) {
    auto [it, wasInserted]{ m_uniformLocations.try_emplace(name, 0) };
    return !wasInserted ? it->second : (it->second = glGetUniformLocation(m_shaderProgramId, name));
}

GLuint Shader::createShaderFromFile(const GLenum type, const std::filesystem::path& fileName) {
    std::ifstream shaderFile{ fileName };
    if (!shaderFile) {
        std::cerr << "Error: Couldn't open file: " << fileName << "\n";
        return 0;
    }

    const GLCharString shaderSource{
        std::istreambuf_iterator<GLchar>{ shaderFile },
        std::istreambuf_iterator<GLchar>{}
    };
    const GLchar* const sourcePtr{ shaderSource.c_str() };

    const GLuint glShader{ glCreateShader(type) };
    glShaderSource(glShader, 1, &sourcePtr, NULL);
    glCompileShader(glShader);

    GLint success{};
    glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
    if (success) {
        return glShader;
    }

    GLint infoLogSize{};
    glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &infoLogSize);

    GLCharString infoLog{};
    infoLog.resize(infoLogSize);
    glGetShaderInfoLog(glShader, infoLogSize, NULL, infoLog.data());

    std::cerr << "Error: Shader compilation failed:\n" << infoLog << '\n';
    return 0;
}

void Shader::deleteShaderProgram() {
    if (m_shaderProgramId) {
        glDeleteProgram(m_shaderProgramId);
        m_shaderProgramId = 0;
    }
}

void Shader::createShaderProgram() {
    if (m_shaderProgramId) {
        return;
    }

    m_shaderProgramId = glCreateProgram();

    const GLuint vertexShader{ createShaderFromFile(GL_VERTEX_SHADER, m_vertexShaderPath) };
    if (!vertexShader) {
        return deleteShaderProgram();
    }

    glAttachShader(m_shaderProgramId, vertexShader);
    glDeleteShader(vertexShader);

    const GLuint fragmentShader{ createShaderFromFile(GL_FRAGMENT_SHADER, m_fragmentShaderPath) };
    if (!fragmentShader) {
        return deleteShaderProgram();
    }

    glAttachShader(m_shaderProgramId, fragmentShader);
    glDeleteShader(fragmentShader);

    if (!m_geometryShaderPath.empty()) {
        const GLuint geometryShader{ createShaderFromFile(GL_GEOMETRY_SHADER, m_geometryShaderPath) };
        if (!geometryShader) {
            return deleteShaderProgram();
        }

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
    glGetShaderiv(m_shaderProgramId, GL_INFO_LOG_LENGTH, &infoLogSize);

    GLCharString infoLog{};
    infoLog.resize(infoLogSize);
    glGetShaderInfoLog(m_shaderProgramId, infoLogSize, NULL, infoLog.data());

    std::cerr << "Error: Program linking failed:\n" << infoLog << '\n';
    deleteShaderProgram();
}

