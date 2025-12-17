#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture2d.h"

#include <glm/glm.hpp>
#include <optional>

struct Material {
    std::optional<Texture2D> diffuse{};
};

#endif // MATERIAL_H
