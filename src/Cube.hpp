#pragma once

#include "OpenGLHeaders.hpp"
#include "Engine.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>

#include <array>

namespace learn {

    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
    };

    class Cube {
    public:
        explicit Cube(const glm::vec3& position, const float angle);
        ~Cube();

        Cube(const Cube&) = delete;
        Cube& operator=(const Cube&) = delete;

        Cube(Cube&& other);
        Cube& operator=(Cube&& other);

        void render(const glm::mat4& view, const glm::mat4& projection) const;

        [[nodiscard]] const glm::vec3& position() const { return m_position; }
        [[nodiscard]] float angle() const { return m_angle; }

    private:
        glm::vec3 m_position;
        float m_angle;

        std::array<Vertex, 24> m_vertices;
        std::array<unsigned int, 36> m_indices;

        GLuint m_vao = 0;
        GLuint m_vbo = 0;
        GLuint m_ebo = 0;

        Shader m_shader;
        Texture m_brick_wall_texture;
        Texture m_container_texture;
        Texture m_awesome_face_texture;
    };

} // namespace learn
