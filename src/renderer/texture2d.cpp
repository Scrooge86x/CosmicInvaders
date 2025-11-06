#include "texture2d.h"

#include <utility>

#include <stb_image.h>

Texture2D::Texture2D(const std::filesystem::path& path) {
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data{ stbi_load(path.string().c_str(), &m_width, &m_height, &m_nChannels, 0) };
    if (!data) {
        return;
    }

    createTextureFromData(data);
    stbi_image_free(data);
}

Texture2D::Texture2D(Texture2D&& other) noexcept
    : m_textureId{ std::exchange(other.m_textureId, 0) }
    , m_width    { std::exchange(other.m_width, 0) }
    , m_height   { std::exchange(other.m_height, 0) }
    , m_nChannels{ std::exchange(other.m_nChannels, 0) }
{}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    deleteTexture();

    m_textureId = std::exchange(other.m_textureId, 0);
    m_width     = std::exchange(other.m_width, 0);
    m_height    = std::exchange(other.m_height, 0);
    m_nChannels = std::exchange(other.m_nChannels, 0);

    return *this;
}

void Texture2D::bind(const unsigned int slotId) const {
    glActiveTexture(GL_TEXTURE0 + slotId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Texture2D::createTextureFromData(const unsigned char* const data) {
    GLint internalFormat{};
    GLenum format{};

    switch (m_nChannels) {
    case 1:
        internalFormat = GL_R8;
        format = GL_RED;
        break;
    case 2:
        internalFormat = GL_RG8;
        format = GL_RG;
        break;
    case 3:
        internalFormat = GL_RGB8;
        format = GL_RGB;
        break;
    case 4:
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
        break;
    default:
        break;
    }

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::deleteTexture() {
    if (m_textureId) {
        glDeleteTextures(1, &m_textureId);
    }

    m_textureId = 0;
    m_width = 0;
    m_height = 0;
    m_nChannels = 0;
}
