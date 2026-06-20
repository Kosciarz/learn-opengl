#include "Cube.hpp"
#include "Engine.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <utility>

namespace learn {

    static const std::filesystem::path SHADER_DIR{SHADER_DIRECTORY};
    static const std::filesystem::path TEXTURE_DIR{TEXTURE_DIRECTORY};

    Cube::Cube(const glm::vec3& position, const float angle)
        : m_position{position},
          m_angle{angle},
          m_shader{SHADER_DIR / "vertex.vert", SHADER_DIR / "fragment.frag"},
          m_brick_wall_texture{TEXTURE_DIR / "wall.jpg"},
          m_container_texture{TEXTURE_DIR / "container.jpg"},
          m_awesome_face_texture{TEXTURE_DIR / "awesomeface.png"} {
        m_vertices = {{
            // front face bottom left
            {
                .position = {-0.5f, -0.5f, 0.5f},
                .uv = {0.0f, 0.0f},
            },
            // front face bottom right
            {
                .position = {0.5f, -0.5f, 0.5f},
                .uv = {1.0f, 0.0f},
            },
            // front face top right
            {
                .position = {0.5f, 0.5f, 0.5f},
                .uv = {1.0f, 1.0f},
            },
            // front face top left
            {
                .position = {-0.5f, 0.5f, 0.5f},
                .uv = {0.0f, 1.0f},
            },
            // back face bottom left
            {
                .position = {0.5f, -0.5f, -0.5f},
                .uv = {0.0f, 0.0f},
            },
            // back face bottom right
            {
                .position = {-0.5f, -0.5f, -0.5f},
                .uv = {1.0f, 0.0f},
            },
            // back face top right
            {
                .position = {-0.5f, 0.5f, -0.5f},
                .uv = {1.0f, 1.0f},
            },
            // back face top left
            {
                .position = {0.5f, 0.5f, -0.5f},
                .uv = {0.0f, 1.0f},
            },
            // left face bottom left
            {
                .position = {-0.5f, -0.5f, -0.5f},
                .uv = {0.0f, 0.0f},
            },
            // left face bottom right
            {
                .position = {-0.5f, -0.5f, 0.5f},
                .uv = {1.0f, 0.0f},
            },
            // left face top right
            {
                .position = {-0.5f, 0.5f, 0.5f},
                .uv = {1.0f, 1.0f},
            },
            // left face top left
            {
                .position = {-0.5f, 0.5f, -0.5f},
                .uv = {0.0f, 1.0f},
            },
            // right face bottom left
            {
                .position = {0.5f, -0.5f, 0.5f},
                .uv = {0.0f, 0.0f},
            },
            // right face bottom right
            {
                .position = {0.5f, -0.5f, -0.5f},
                .uv = {1.0f, 0.0f},
            },
            // right face top right
            {
                .position = {0.5f, 0.5f, -0.5f},
                .uv = {1.0f, 1.0f},
            },
            // right face top left
            {
                .position = {0.5f, 0.5f, 0.5f},
                .uv = {0.0f, 1.0f},
            },
            // top face bottom left
            {
                .position = {-0.5f, 0.5f, 0.5f},
                .uv = {0.0f, 0.0f},
            },
            // top face bottom right
            {
                .position = {0.5f, 0.5f, 0.5f},
                .uv = {1.0f, 0.0f},
            },
            // top face top right
            {
                .position = {0.5f, 0.5f, -0.5f},
                .uv = {1.0f, 1.0f},
            },
            // top face top left
            {
                .position = {-0.5f, 0.5f, -0.5f},
                .uv = {0.0f, 1.0f},
            },
            // bottom face bottom left
            {
                .position = {-0.5f, -0.5f, -0.5f},
                .uv = {0.0f, 0.0f},
            },
            // bottom face bottom right
            {
                .position = {0.5f, -0.5f, -0.5f},
                .uv = {1.0f, 0.0f},
            },
            // bottom face top right
            {
                .position = {0.5f, -0.5f, 0.5f},
                .uv = {1.0f, 1.0f},
            },
            // bottom face top left
            {
                .position = {-0.5f, -0.5f, 0.5f},
                .uv = {0.0f, 1.0f},
            },
        }};

        // clang-format off
        m_indices = {
            // front face
                0, 1, 2,
                2, 3, 0,
            // back face
                4, 5, 6,
                6, 7, 4,
            // left face
                8, 9, 10,
                10, 11, 8,
            // right face
                12, 13, 14,
                14, 15, 12,
            // top face
                16, 17, 18,
                18, 19, 16,
            // bottom face
                20, 21, 22,
                22, 23, 20,
        };
        // clang-format on

        glCreateVertexArrays(1, &m_vao);
        glCreateBuffers(1, &m_vbo);
        glCreateBuffers(1, &m_ebo);

        // upload data to buffers
        glNamedBufferData(
            m_vbo, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
        glNamedBufferData(
            m_ebo, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

        // attach buffers to vao
        glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(Vertex));
        glVertexArrayElementBuffer(m_vao, m_ebo);

        // attributes
        // position
        glEnableVertexArrayAttrib(m_vao, 0);
        glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
        glVertexArrayAttribBinding(m_vao, 0, 0);

        // texture coordinates
        glEnableVertexArrayAttrib(m_vao, 1);
        glVertexArrayAttribFormat(m_vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv));
        glVertexArrayAttribBinding(m_vao, 1, 0);
    }

    Cube::~Cube() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    Cube::Cube(Cube&& other)
        : m_position{std::move(other.m_position)},
          m_angle{other.m_angle},
          m_vertices{std::move(other.m_vertices)},
          m_indices{std::move(other.m_indices)},
          m_shader{std::move(other.m_shader)},
          m_brick_wall_texture{std::move(other.m_brick_wall_texture)},
          m_container_texture{std::move(other.m_container_texture)},
          m_awesome_face_texture{std::move(other.m_awesome_face_texture)},
          m_vao{std::exchange(other.m_vao, 0)},
          m_vbo{std::exchange(other.m_vbo, 0)},
          m_ebo{std::exchange(other.m_ebo, 0)} {}

    Cube& Cube::operator=(Cube&& other) {
        if (this != &other) {
            glDeleteVertexArrays(1, &m_vao);
            glDeleteBuffers(1, &m_vbo);
            glDeleteBuffers(1, &m_ebo);

            m_position = std::move(other.m_position);
            m_angle = other.m_angle;
            m_vertices = std::move(other.m_vertices);
            m_indices = std::move(other.m_indices);
            m_shader = std::move(other.m_shader);
            m_brick_wall_texture = std::move(other.m_brick_wall_texture);
            m_container_texture = std::move(other.m_container_texture);
            m_awesome_face_texture = std::move(other.m_awesome_face_texture);
            m_vao = std::exchange(other.m_vao, 0);
            m_vbo = std::exchange(other.m_vbo, 0);
            m_ebo = std::exchange(other.m_ebo, 0);
        }

        return *this;
    }
    void Cube::render(const glm::mat4& view, const glm::mat4& projection) const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_position);
        model = glm::rotate(model, glm::radians(m_angle), glm::vec3{1.0f, 0.3f, 0.5f});

        m_shader.use();
        glUniform1i(m_shader.uniform_location("texture0"), 0);
        glUniform1i(m_shader.uniform_location("texture1"), 1);

        glUniformMatrix4fv(m_shader.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(m_shader.uniform_location("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(
            m_shader.uniform_location("projection"), 1, GL_FALSE, glm::value_ptr(projection));

        m_brick_wall_texture.bind(0);
        m_awesome_face_texture.bind(1);

        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    }

} // namespace learn
