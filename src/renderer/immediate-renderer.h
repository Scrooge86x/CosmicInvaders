#pragma once

#ifndef IMMEDIATE_RENDERER_H
#define IMMEDIATE_RENDERER_H

#include "renderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

class ImmediateRenderer : public Renderer<ImmediateRenderer> {
public:
	static ImmediateRenderer& getInstance() {
		static ImmediateRenderer instance;
		return instance;
	}

	void initImmediateRenderer();

	ImmediateRenderer(const ImmediateRenderer&) = delete;
	ImmediateRenderer& operator=(const ImmediateRenderer&) = delete;

	ImmediateRenderer(ImmediateRenderer&&) = delete;
	ImmediateRenderer& operator=(ImmediateRenderer&&) = delete;

	void beginFrame();
	void endFrame();
	void submit(const Model& object, Shader& shader, const glm::mat4& transform = { 1.f });
	void flush();

	void setProjection(const float& aspectRatio);

private:
	friend Renderer<ImmediateRenderer>;
	ImmediateRenderer() {};

	glm::mat4 m_view{ glm::lookAt(
		glm::vec3{ 5.f, 1.f, 5.f },
		glm::vec3{ 0.f, 0.f, 0.f },
		glm::vec3{ 0.f, 1.f, 0.f }
	) };

	glm::mat4 m_projection{};
	
};

#endif