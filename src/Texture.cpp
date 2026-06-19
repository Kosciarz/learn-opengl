#include "Texture.hpp"
#include "OpenGLHeaders.hpp"

#include "stb_image.h"

#include <filesystem>
#include <stdexcept>
#include <format>
#include <cmath>

namespace learn {

    Texture::Texture(const std::filesystem::path& path) {
        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        unsigned char* image_data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

        if (!image_data) {
            throw std::runtime_error{std::format("Failed to load texture: {}", path.string())};
        }

        GLenum internal_format;
        GLenum data_format;

        switch (channels) {
        case 3:
            internal_format = GL_RGB8;
            data_format = GL_RGB;
            break;
        case 4:
            internal_format = GL_RGBA8;
            data_format = GL_RGBA;
            break;
        default:
            stbi_image_free(image_data);
            throw std::runtime_error("Unsupported texture format");
        }

        const int mip_levels = 1 + static_cast<int>(std::floor(std::log2(std::max(width, height))));

        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

        glTextureStorage2D(m_id, mip_levels, internal_format, width, height);

        glTextureSubImage2D(
            m_id, 0, 0, 0, width, height, data_format, GL_UNSIGNED_BYTE, image_data);

        glGenerateTextureMipmap(m_id);

        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(image_data);
    }

    Texture::~Texture() {
        if (m_id) {
            glDeleteTextures(1, &m_id);
        }
    }

    Texture::Texture(Texture&& other) noexcept
        : m_id{other.m_id} {
        other.m_id = 0;
    }

    Texture& Texture::operator=(Texture&& other) noexcept {
        if (this != &other) {
            if (m_id) {
                glDeleteTextures(1, &m_id);
            }

            m_id = other.m_id;
            other.m_id = 0;
        }

        return *this;
    }

} // namespace learn
