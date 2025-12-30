#include "renderer.h"

#include "material.h"
#include "lighting.h"
#include "model.h"
#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer() : m_shaders{
	Shader{ "assets/shaders/vertex-test.glsl", "assets/shaders/fragment-test.glsl" }
} {
	glEnable(GL_DEPTH_TEST);
}

void Renderer::beginFrame(const Lighting& lighting, const Camera& camera) {
	m_cachedCamera = &camera;

	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shaders[ShaderType::Main].use();
	m_shaders[ShaderType::Main].setVec3("u_lighting.ambient", lighting.ambient);
	m_shaders[ShaderType::Main].setVec3("u_lighting.sunPosition", lighting.sunPosition);
	m_shaders[ShaderType::Main].setVec3("u_lighting.sunColor", lighting.sunColor);
	m_shaders[ShaderType::Main].setVec3("u_cameraPos", m_cachedCamera->getPosition());
}

void Renderer::endFrame() {}

void Renderer::draw(const Model& object, const glm::mat4& transform) {
	if (!m_cachedCamera) {
		return;
	}

	glm::mat3 normal{ glm::transpose(glm::inverse(glm::mat3{ transform })) };

	m_shaders[ShaderType::Main].setMat3("u_normal", normal);
	m_shaders[ShaderType::Main].setMat4("u_mvp", m_cachedCamera->getViewProjection() * transform);

	for (const auto& mesh : object.getMeshes()) {
		const auto& material{ *mesh.getMaterial() };
		if (material.diffuse) {
			material.diffuse->bind(0);
			m_shaders[ShaderType::Main].setInt("u_material.diffuse", 0);
		}

		m_shaders[ShaderType::Main].setVec3("u_material.specularColor", material.specularColor);
		m_shaders[ShaderType::Main].setFloat("u_material.specularStrength", material.specularStrength);
		m_shaders[ShaderType::Main].setFloat("u_material.shininess", material.shininess);

		glBindVertexArray(mesh.getVao());
		glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, NULL);
	}
}