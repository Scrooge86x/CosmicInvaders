#include "mesh.h"

#include <utility>
#include <vector>

Mesh::Mesh(
    const std::span<Vertex> vertices,
    const std::span<GLuint> indices,
    const std::shared_ptr<Material> material)
        : m_vertexCount{ static_cast<GLsizei>(vertices.size()) }
        , m_indexCount{ static_cast<GLsizei>(indices.size()) }
        , m_material{ material } {
    createMesh(vertices, indices);
}

Mesh::Mesh(
    const aiMesh& mesh,
    const std::shared_ptr<Material> material,
    const glm::mat4& transform)
        : m_material{ material }
        , m_indexCount{ static_cast<GLsizei>(mesh.mNumFaces * 3) } // Assumes aiProcess_Triangulate was used
        , m_vertexCount{ static_cast<GLsizei>(mesh.mNumVertices) } {
    std::vector<Vertex> vertices{};
    vertices.reserve(m_vertexCount);

    const bool hasNormals{ mesh.HasNormals() };
    const bool hasTextureCoords{ mesh.HasTextureCoords(0) };
    const glm::mat3 normalMatrix{ glm::transpose(glm::inverse(glm::mat3{ transform })) };

    for (unsigned int i{}; i < mesh.mNumVertices; ++i) {
        vertices.emplace_back(
            glm::vec3{ transform * glm::vec4{
                mesh.mVertices[i].x,
                mesh.mVertices[i].y,
                mesh.mVertices[i].z,
                1.f
            } },
            hasNormals ? glm::normalize(normalMatrix * glm::vec3{
                mesh.mNormals[i].x,
                mesh.mNormals[i].y,
                mesh.mNormals[i].z
            }) : glm::vec3{},
            hasTextureCoords ? glm::vec2{
                mesh.mTextureCoords[0][i].x,
                mesh.mTextureCoords[0][i].y
            } : glm::vec2{}
        );
    }

    std::vector<GLuint> indices{};
    indices.reserve(m_indexCount);

    for (unsigned int i{}; i < mesh.mNumFaces; ++i) {
        const aiFace& face{ mesh.mFaces[i] };
        for (unsigned int j{}; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    createMesh(vertices, indices);
}

Mesh::Mesh(Mesh&& other) noexcept
    : m_vao        { std::exchange(other.m_vao, 0) }
    , m_vbo        { std::exchange(other.m_vbo, 0) }
    , m_ebo        { std::exchange(other.m_ebo, 0) }
    , m_vertexCount{ std::exchange(other.m_vertexCount, 0) }
    , m_indexCount { std::exchange(other.m_indexCount, 0) }
    , m_material   { std::move(other.m_material) }
{}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    deleteMesh();

    m_vao         = std::exchange(other.m_vao, 0);
    m_vbo         = std::exchange(other.m_vbo, 0);
    m_ebo         = std::exchange(other.m_ebo, 0);
    m_vertexCount = std::exchange(other.m_vertexCount, 0);
    m_indexCount  = std::exchange(other.m_indexCount, 0);
    m_material    = std::move(other.m_material);

    return *this;
}

void Mesh::createMesh(
    const std::span<Vertex> vertices,
    const std::span<GLuint> indices
) {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));

    glBindVertexArray(0);
}

void Mesh::deleteMesh() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);

    m_vao = 0;
    m_vbo = 0;
    m_ebo = 0;
}
