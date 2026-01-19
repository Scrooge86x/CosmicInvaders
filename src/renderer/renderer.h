#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include <glm/glm.hpp>
#include <array>

class Camera;
class Model;
struct Lighting;

/** 
 * @brief Responsible for rendering 3D models using OpenGL.
 *
 * The Renderer class coordinates the rendering process for a single frame.
 * It uses Shader instances to issue draw calls, uploads per-frame data
 * such as lighting and camera parameters, and renders models provided
 * by the caller.
 *
 * Shader programs themselves are managed by the Shader class. The Renderer
 * only owns instances of shaders and uses them during rendering.
 *
 * The active camera is provided at the beginning of each frame via
 * beginFrame() and cached temporarily for draw calls within that frame.
 */

class Renderer {
public:
    /**
     * @brief Constructs the renderer and initializes OpenGL state.
     *
     * Initializes shader instances and enables depth testing.
     */
    Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    /**
     * @brief Prepares the renderer for a new frame.
     *
     * Clears frame buffers, activates appropriate shaders and uploads
     * per-frame data such as lighting parameters and camera position.
     * The provided camera is expected to remain valid for the duration
     * of the frame.
     *
     * @param lighting Scene lighting data used for the frame.
     * @param camera Camera used to generate view and projection matrices.
     */
    void beginFrame(const Lighting& lighting, const Camera& camera);

    /**
     * @brief Finishes the current frame.
     *
     * Intended as a synchronization point for frame-based rendering logic.
     * Currently performs no operations.
     */
    void endFrame();

    /**
     * @brief Renders a model using the currently active frame state.
     *
     * Uses the camera provided in beginFrame() to compute transformation
     * matrices and renders all meshes contained in the model using
     * their associated materials.
     *
     * If beginFrame() has not been called, this function performs no rendering.
     *
     * @param object Model to be rendered.
     * @param transform Model transformation matrix.
     */
    void draw(const Model& object, const glm::mat4& transform);

private:
    enum ShaderType {
        MeshLit,
        COUNT
    };

    std::array<Shader, ShaderType::COUNT> m_shaders;
    const Camera* m_cachedCamera{};
};

#endif 