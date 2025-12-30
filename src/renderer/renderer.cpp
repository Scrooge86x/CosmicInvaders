#include "renderer.h"

#include "material.h"

Renderer::Renderer() : m_shaders{
	Shader{ "assets/shaders/vertex-test.glsl", "assets/shaders/fragment-test.glsl" }
} {
	glEnable(GL_DEPTH_TEST);
}

void Renderer::beginFrame() {
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::onceAFrame(const Lighting& lighting, const glm::mat4& camera, const glm::vec3& cameraPosition) {
	m_shaders[0].use();
	m_shaders[0].setMat4("u_mvp", camera);
	m_shaders[0].setVec3("u_lighting.ambient", lighting.ambient);
	m_shaders[0].setVec3("u_lighting.sunPosition", lighting.sunPosition);
	m_shaders[0].setVec3("u_lighting.sunColor", lighting.sunColor);
	m_shaders[0].setVec3("u_cameraPos", cameraPosition);
}

void Renderer::draw(const Model& object, const glm::mat3& normal) {
	m_shaders[0].use();
	m_shaders[0].setMat4("u_normal", normal);

	for (const auto& mesh : object.getMeshes()) {
		const auto& material{ *mesh.getMaterial() };

		if (material.diffuse) {
			material.diffuse->bind(0);
			m_shaders[0].setInt("u_material.diffuse", 0);
		}

		m_shaders[0].setVec3("u_material.specularColor", material.specularColor);
		m_shaders[0].setFloat("u_material.specularStrength", material.specularStrength);
		m_shaders[0].setFloat("u_material.shininess", material.shininess);

		glBindVertexArray(mesh.getVao());
		glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, NULL);
	}
}