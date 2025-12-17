#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture2d.h"

#include <glm/glm.hpp>
#include <optional>

struct Material {
    std::optional<Texture2D> diffuse{};
    glm::vec3 specularColor{ 1.f };
    float specularStrength{ 1.f };
    float shininess{ 32.f };
};

#endif // MATERIAL_H
