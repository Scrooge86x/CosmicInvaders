#include "model-store.h"

#include "model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

std::shared_ptr<Model> ModelStore::load(
    const std::filesystem::path& path,
    const float scale
) {
    auto& modelScalesMap{ m_modelCache[path] };

    const auto it{ modelScalesMap.find(scale) };
    if (it != modelScalesMap.end()) {
        if (auto modelPtr{ it->second.lock() }) {
            return modelPtr;
        }
    }

    const auto model{ std::make_shared<Model>(path, glm::scale(glm::mat4{ 1.f }, glm::vec3{ scale }))};
    modelScalesMap[scale] = model;
    return model;
}
