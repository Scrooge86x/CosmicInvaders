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

/**
 * @brief 3D model composed of multiple meshes.
 *
 * Loads mesh and material data using Assimp
 */
class Model {
public:
    /**
     * @brief Loads a model from disk.
     *
     * @param path Path to the model file.
     * @param transform Root transform applied to the model.
     */
    explicit Model(
        const std::filesystem::path& path,
        const glm::mat4& transform = { 1.f }
    );

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    Model(Model&& other) noexcept = default;
    Model& operator=(Model&& other) noexcept = default;

    /**
     * @brief Returns all meshes in this model.
     */
    [[nodiscard]] const std::vector<Mesh>& getMeshes() const {
        return m_meshes;
    }

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
