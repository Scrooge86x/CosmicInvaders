#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include <glm/glm.hpp>
#include <array>

class Camera;
class Model;
struct Lighting;

class Renderer {
public:
	Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	void beginFrame(const Lighting& lighting, const Camera& camera);
	void endFrame();

	void draw(const Model& object, const glm::mat4& transform);

private:
	enum ShaderTypes {
		MAIN = 0,
		COUNT
	};

	std::array<Shader, ShaderTypes::COUNT> m_shaders;
	const Camera* m_cachedCamera{};
};

#endif 