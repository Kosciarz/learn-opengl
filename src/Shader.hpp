#pragma once

#include <glad/gl.h>

#include <filesystem>

namespace learn {

    class Shader {
    public:
        Shader(const std::filesystem::path& vertex_path,
               const std::filesystem::path& fragment_path);
        ~Shader();

        [[nodiscard]] GLuint program() const { return m_program; }

        void use() const { glUseProgram(m_program); }
        void unuse() const { glUseProgram(0); }

    private:
        GLuint m_program;
    };

} // namespace learn
