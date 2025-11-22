#include "renderer.h"

void Renderer::draw(const Model& object, Shader& shader) const {
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