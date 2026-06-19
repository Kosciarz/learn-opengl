#pragma once

#include "OpenGLHeaders.hpp"

#include <filesystem>

namespace learn {

    class Texture {
    public:
        explicit Texture(const std::filesystem::path& path);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        [[nodiscard]] GLuint id() const { return m_id; }

        void bind(const GLuint unit) const { glBindTextureUnit(unit, m_id); }

    private:
        GLuint m_id{};
    };

} // namespace learn
