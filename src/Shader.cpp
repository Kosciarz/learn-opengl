#include "Shader.hpp"
#include "OpenGLHeaders.hpp"

#include <fstream>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <format>

namespace {

    std::string read_file(const std::filesystem::path& path) {
        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error{std::format("Failed to open file: {}", path.string())};
        }

        return std::string{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    }

    GLuint compile_shader(const GLenum type, const std::string& source) {
        const GLchar* source_ptr = static_cast<const GLchar*>(source.c_str());

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source_ptr, nullptr);
        glCompileShader(shader);

        GLint shader_compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
        if (shader_compiled != GL_TRUE) {
            GLsizei log_length{0};
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
            std::vector<GLchar> log(log_length);
            glGetShaderInfoLog(shader, log_length, &log_length, log.data());

            throw std::runtime_error{std::format("Failed to compile {} shader: {}",
                                                 type == GL_VERTEX_SHADER ? "vertex" : "fragment",
                                                 log.data())};
        }

        return shader;
    }

    GLuint link_program(const GLuint vertex_shader, const GLuint fragment_shader) {
        GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        GLint program_linked;
        glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
        if (program_linked != GL_TRUE) {
            GLsizei log_length{0};
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
            std::vector<GLchar> log(log_length);
            glGetProgramInfoLog(program, log_length, &log_length, log.data());

            throw std::runtime_error{"Failed to link program"};
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return program;
    }

} // namespace

namespace learn {

    Shader::Shader(const std::filesystem::path& vertex_path,
                   const std::filesystem::path& fragment_path) {
        const auto vertex_source = read_file(vertex_path);
        const auto fragment_source = read_file(fragment_path);

        const GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
        const GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);

        m_program = link_program(vertex_shader, fragment_shader);
    }

    Shader::~Shader() {
        if (m_program) {
            glDeleteProgram(m_program);
        }
    }

    Shader::Shader(Shader&& other) noexcept
        : m_program{other.m_program} {
        other.m_program = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept {
        if (this != &other) {
            if (m_program) {
                glDeleteProgram(m_program);
            }

            m_program = other.m_program;
            other.m_program = 0;
        }

        return *this;
    }

} // namespace learn
