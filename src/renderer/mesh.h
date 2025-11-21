#pragma once

#ifndef MESH_H
#define MESH_H

#include <span>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>

#include "material.h"

struct Vertex {
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec2 uv{};
};

class Mesh {
public:
    Mesh(
        const std::span<Vertex> vertices,
        const std::span<GLuint> indices,
        const std::shared_ptr<Material> material
    );
    Mesh(
        const aiMesh& mesh,
        const std::shared_ptr<Material> material,
        const glm::mat4& transform = { 1.f }
    );

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    ~Mesh() {
        deleteMesh();
    }

    [[nodiscard]] GLuint getVao() const { return m_vao; }
    [[nodiscard]] GLuint getVbo() const { return m_vao; }
    [[nodiscard]] GLuint getEbo() const { return m_vao; }
    [[nodiscard]] GLsizei getVertexCount() const { return m_vertexCount; }
    [[nodiscard]] GLsizei getIndexCount() const { return m_indexCount; }
    [[nodiscard]] std::shared_ptr<Material> getMaterial() const { return m_material; }

private:
    void createMesh(
        const std::span<Vertex> vertices,
        const std::span<GLuint> indices
    );
    void deleteMesh();

    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_ebo{};

    std::shared_ptr<Material> m_material{};
    GLsizei m_vertexCount{};
    GLsizei m_indexCount{};
};

#endif // MESH_H
