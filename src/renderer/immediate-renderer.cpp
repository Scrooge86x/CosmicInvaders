#include "immediate-renderer.h"

void ImmediateRenderer::initImmediateRenderer() {
}

void ImmediateRenderer::setProjection(const float& aspectRatio) {
    m_projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
}

void ImmediateRenderer::beginFrame() {
    glClearColor(0.f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ImmediateRenderer::submit(const Model& object, Shader& shader, const glm::mat4& transform) {
    shader.use();
    shader.setMat4("u_model", transform);
    shader.setMat4("u_view", m_view);
    shader.setMat4("u_projection", m_projection);

    for (const auto& mesh : object.getMeshes()) {
        const auto& [diffuse] { *mesh.getMaterial() };
        if (diffuse) {
            diffuse->bind(0);
            shader.setInt("u_material.diffuse", 0);
        }

        glBindVertexArray(mesh.getVao());
        glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, NULL);
    }
}