#pragma once

#ifndef MESH_H
#define MESH_H

#include <span>

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
        Material&& material
    );
    Mesh(const aiScene* scene, const unsigned int meshIndex);

    ~Mesh() {
        deleteMesh();
    }

    [[nodiscard]] GLuint getVao() const { return m_vao; }
    [[nodiscard]] GLuint getVbo() const { return m_vao; }
    [[nodiscard]] GLuint getEbo() const { return m_vao; }
    [[nodiscard]] GLsizei getVertexCount() const { return m_vertexCount; }
    [[nodiscard]] GLsizei getIndexCount() const { return m_indexCount; }
    [[nodiscard]] const Material& getMaterial() const { return m_material; }

private:
    void createMesh(
        const std::span<Vertex> vertices,
        const std::span<GLuint> indices
    );
    void deleteMesh();

    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_ebo{};

    Material m_material;
    GLsizei m_vertexCount{};
    GLsizei m_indexCount{};
};

#endif // MESH_H
