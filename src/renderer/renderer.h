#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include <glm/glm.hpp>
#include <array>

class Model;
struct Lighting;

class Renderer {
public:
	Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	void beginFrame();
	void endFrame();

	void draw(const Model& object, const glm::mat3& normal);
	void onceAFrame(const Lighting& lighting, const glm::mat4& camera, const glm::vec3& cameraPosition);

private:
	enum ShaderTypes {
		MAIN = 0,
		COUNT
	};

	std::array<Shader, ShaderTypes::COUNT> m_shaders;
};

#endif 