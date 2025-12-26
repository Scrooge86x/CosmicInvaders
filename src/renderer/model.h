#pragma once

#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

#include <glm/glm.hpp>

#include <vector>
#include <filesystem>

struct Material;
struct aiScene;
struct aiNode;

class Model {
public:
    explicit Model(
        const std::filesystem::path& path,
        const glm::mat4& transform = { 1.f }
    );

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    Model(Model&& other) noexcept = default;
    Model& operator=(Model&& other) noexcept = default;

    const std::vector<Mesh>& getMeshes() const { return m_meshes; }

private:
    void processNode(
        const aiScene* const scene,
        const aiNode* const node,
        const glm::mat4& parentTransform
    );

    std::vector<Mesh> m_meshes{};
    std::vector<std::shared_ptr<Material>> m_materials{};
};

#endif // MODEL_H
