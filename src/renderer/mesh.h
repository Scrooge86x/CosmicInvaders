#pragma once

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <span>
#include <memory>

struct aiMesh;
struct Material;

/**
 * @brief Single mesh vertex.
 *
 * Contains all vertex attributes required for rendering.
 */
struct Vertex {
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec2 uv{};
};

/**
 * @brief Renderable mesh stored on the GPU.
 *
 * Owns the OpenGL buffers and VAO needed to draw
 * indexed geometry.
 */
class Mesh {
public:
    /**
     * @brief Creates a mesh from raw vertex and index data.
     *
     * @param vertices Vertex data.
     * @param indices Index data.
     * @param material Material shared by this mesh.
     *
     * @throws std::runtime_error If mesh creation fails.
     */
    Mesh(
        const std::span<Vertex> vertices,
        const std::span<GLuint> indices,
        const std::shared_ptr<Material> material
    );

    /**
     * @brief Creates a mesh from an Assimp mesh.
     *
     * @param mesh Assimp mesh source.
     * @param material Material used by this mesh.
     * @param transform Transform applied to vertex positions.
     *
     * @throws std::runtime_error If mesh creation fails.
     */
    Mesh(
        const aiMesh& mesh,
        const std::shared_ptr<Material> material,
        const glm::mat4& transform = { 1.f }
    );

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    /**
     * @brief Destroys the mesh and releases GPU resources.
     */
    ~Mesh() {
        deleteMesh();
    }

    [[nodiscard]] GLuint getVao() const { return m_vao; }
    [[nodiscard]] GLuint getVbo() const { return m_vbo; }
    [[nodiscard]] GLuint getEbo() const { return m_ebo; }
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
