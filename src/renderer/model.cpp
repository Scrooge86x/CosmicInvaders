#include "model.h"

#include "material.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <format>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string_view>

[[nodiscard]] static std::filesystem::path findTextureInAssets(
    const std::filesystem::path& searchRoot,
    const std::filesystem::path& fullTexturePath
) {
    if (!std::filesystem::exists(searchRoot) || !std::filesystem::is_directory(searchRoot)) {
        throw std::runtime_error{ std::format(R"("{}" is not a directory.)", searchRoot.generic_string()) };
    }

    const auto texturePathString{ fullTexturePath.string() };
    std::string_view targetFileName{ texturePathString };

    const auto lastSeparatorPos{ targetFileName.find_last_of("\\/") };
    if (lastSeparatorPos != std::string_view::npos) {
        targetFileName.remove_prefix(lastSeparatorPos + 1);
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator{ searchRoot }) {
        if (entry.is_regular_file() && entry.path().filename() == targetFileName) {
            return entry.path();
        }
    }

    throw std::runtime_error{ std::format(R"("{}" was not found.)", texturePathString) };
}

Model::Model(
    const std::filesystem::path& path,
    const glm::mat4& transform
) {
    Assimp::Importer importer{};
    const aiScene* scene{ importer.ReadFile(
        path.string(),
        aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs
    ) };
    if (!scene) {
        throw std::runtime_error{ std::format("Assimp failed to parse: {}", path.generic_string()) };
    }

    m_materials.reserve(scene->mNumMaterials);

    aiString texturePath{};
    for (unsigned int i{}; i < scene->mNumMaterials; ++i) {
        auto materialPtr{ std::make_shared<Material>() };

        aiMaterial* material{ scene->mMaterials[i] };
        if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
            material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
            try {
                if (texturePath.C_Str()[0] == '*') {
                    materialPtr->diffuse = Texture2D{ *scene->mTextures[std::atoi(texturePath.C_Str() + 1)] };
                } else {
                    const auto textureAssetPath{ findTextureInAssets(path.parent_path(), texturePath.C_Str()) };
                    materialPtr->diffuse = Texture2D{ textureAssetPath };
                }
            } catch (const std::exception& exception) {
                std::cerr << "Error when loading a texture: " << exception.what() << '\n';
            }
        }

        m_materials.emplace_back(materialPtr);
    }

    m_meshes.reserve(scene->mNumMeshes);
    processNode(scene, scene->mRootNode, transform);
}

void Model::processNode(
    const aiScene* const scene,
    const aiNode* const node,
    const glm::mat4& parentTransform
) {
    const aiMatrix4x4& from{ node->mTransformation };
    const glm::mat4 nodeTransform{ parentTransform * glm::mat4{
        from.a1, from.b1, from.c1, from.d1,
        from.a2, from.b2, from.c2, from.d2,
        from.a3, from.b3, from.c3, from.d3,
        from.a4, from.b4, from.c4, from.d4,
    } };

    for (unsigned int i{}; i < node->mNumMeshes; ++i) {
        const aiMesh* const mesh{ scene->mMeshes[node->mMeshes[i]] };
        m_meshes.emplace_back(*mesh, m_materials[mesh->mMaterialIndex], nodeTransform);
    }

    for (unsigned int i{}; i < node->mNumChildren; ++i) {
        processNode(scene, node->mChildren[i], nodeTransform);
    }
}
