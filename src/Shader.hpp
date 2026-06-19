#pragma once

#include "OpenGLHeaders.hpp"

#include <filesystem>

namespace learn {

    class Shader {
    public:
        explicit Shader(const std::filesystem::path& vertex_path,
                        const std::filesystem::path& fragment_path);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        [[nodiscard]] GLuint program() const { return m_program; }

        void use() const { glUseProgram(m_program); }
        void unuse() const { glUseProgram(0); }
        [[nodiscard]] GLint uniform_location(const std::string& name) const {
            return glGetUniformLocation(m_program, name.c_str());
        }

    private:
        GLuint m_program;
    };

} // namespace learn
