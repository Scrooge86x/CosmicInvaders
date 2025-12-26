#pragma once

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>

#include <filesystem>

struct aiTexture;

class Texture2D {
public:
    explicit Texture2D(const std::filesystem::path& path);
    explicit Texture2D(const aiTexture& texture);

    ~Texture2D() {
        deleteTexture();
    }

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

    void bind(const unsigned int slotId) const;

    void unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    [[nodiscard]] GLuint getId() const {
        return m_textureId;
    }

    [[nodiscard]] int getWidth() const {
        return m_width;
    }

    [[nodiscard]] int getHeight() const {
        return m_height;
    }

    [[nodiscard]] int getChannelCount() const {
        return m_nChannels;
    }

private:
    void createTextureFromData(const unsigned char* const data);
    void deleteTexture();

    GLuint m_textureId{};
    int m_width{};
    int m_height{};
    int m_nChannels{};
};

#endif // TEXTURE2D_H
