#pragma once

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>

#include <filesystem>

struct aiTexture;

/**
 * @brief 2D texture wrapper.
 *
 * Loads texture data and manages its OpenGL lifetime.
 */
class Texture2D {
public:
    /**
     * @brief Loads a texture from a file.
     *
     * @throws std::runtime_error If texture creation fails.
     */
    explicit Texture2D(const std::filesystem::path& path);

    /**
     * @brief Creates a texture from Assimp data.
     *
     * @throws std::runtime_error If texture creation fails.
     */
    explicit Texture2D(const aiTexture& texture);

    /**
     * @brief Destroys the texture.
     */
    ~Texture2D() {
        deleteTexture();
    }

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

    /**
     * @brief Binds the texture to a texture unit.
     *
     * @param slotId Texture unit index.
     */
    void bind(const unsigned int slotId) const noexcept;

    void unbind() const noexcept {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /**
     * @brief Returns the OpenGL texture object ID.
     * @return OpenGL texture object ID.
     */
    [[nodiscard]] GLuint getId() const noexcept {
        return m_textureId;
    }

    [[nodiscard]] int getWidth() const noexcept {
        return m_width;
    }

    [[nodiscard]] int getHeight() const noexcept {
        return m_height;
    }

    [[nodiscard]] int getChannelCount() const noexcept {
        return m_nChannels;
    }

private:
    void createTextureFromData(const unsigned char* const data);
    void deleteTexture() noexcept;

    GLuint m_textureId{};
    int m_width{};
    int m_height{};
    int m_nChannels{};
};

#endif // TEXTURE2D_H
