#pragma once

#ifndef MODEL_STORE_H
#define MODEL_STORE_H

#include <filesystem>
#include <unordered_map>
#include <memory>
#include <utility>

class Model;

/**
 * @brief Centralized cache for loaded models.
 *
 * Prevents loading the same model multiple times
 * for identical scale values.
 */
class ModelStore {
public:
    ModelStore() = default;

    ModelStore(const ModelStore&) = delete;
    ModelStore& operator=(const ModelStore&) = delete;

    ModelStore(ModelStore&& other) noexcept = default;
    ModelStore& operator=(ModelStore&& other) noexcept = default;

    /**
     * @brief Loads or retrieves a cached model.
     *
     * @param path Model file path.
     * @param scale Uniform scale applied to the model.
     * @return Shared pointer to the model.
     */
    [[nodiscard]] std::shared_ptr<Model> load(
        const std::filesystem::path& path,
        const float scale = { 1.f }
    );

private:
    using ModelScalesMap = std::unordered_map<float, std::weak_ptr<Model>>;
    std::unordered_map<std::filesystem::path, ModelScalesMap> m_modelCache{};
};

#endif // MODEL_STORE_H
