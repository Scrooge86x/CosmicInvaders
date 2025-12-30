#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include <array>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "model.h"
#include "shader.h"
#include "lighting.h"

class Renderer {
public:
	enum ShaderTypes : size_t {
		MAIN = 0,
		COUNT
	};

	Renderer();

	void beginFrame();

	void endFrame();

	void draw(const Model& object, const glm::mat3& normal);

	void onceAFrame(const Lighting& lighting, const glm::highp_mat4 camera, const glm::vec3& cameraPosition);

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

private:
	std::array<Shader, ShaderTypes::COUNT> m_shaders;
};

#endif 