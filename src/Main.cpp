#include "Engine.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <print>
#include <array>
#include <filesystem>

static const std::filesystem::path SHADER_DIR{SHADER_DIRECTORY};
static const std::filesystem::path TEXTURE_DIR{TEXTURE_DIRECTORY};

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texture_coords;
};

int main() {
    try {
        learn::Engine engine;

        std::array<Vertex, 4> vertices{{
            {
                .position = {-0.5f, -0.5f, 0.0f},
                .color = {1.0f, 0.0f, 0.0f},
                .texture_coords = {0.0f, 0.0f},
            },
            {
                .position = {0.5f, -0.5f, 0.0f},
                .color = {0.0f, 1.0f, 0.0f},
                .texture_coords = {1.0f, 0.0f},
            },
            {
                .position = {0.5f, 0.5f, 0.0f},
                .color = {0.0f, 0.0f, 1.0f},
                .texture_coords = {1.0f, 1.0f},
            },
            {
                .position = {-0.5f, 0.5f, 0.0f},
                .color = {1.0f, 1.0f, 0.0f},
                .texture_coords = {0.0f, 1.0f},
            },
        }};

        std::array<unsigned int, 6> indices{0, 1, 2, 2, 3, 0};

        GLuint vao{0};
        glCreateVertexArrays(1, &vao);

        GLuint vbo{0};
        glCreateBuffers(1, &vbo);

        GLuint ebo{0};
        glCreateBuffers(1, &ebo);

        // upload data to buffers
        glNamedBufferData(vbo, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glNamedBufferData(
            ebo, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // attach buffers to vao
        glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
        glVertexArrayElementBuffer(vao, ebo);

        // attributes
        // position
        glEnableVertexArrayAttrib(vao, 0);
        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
        glVertexArrayAttribBinding(vao, 0, 0);

        // color
        glEnableVertexArrayAttrib(vao, 1);
        glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
        glVertexArrayAttribBinding(vao, 1, 0);

        // texture coordinates
        glEnableVertexArrayAttrib(vao, 2);
        glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texture_coords));
        glVertexArrayAttribBinding(vao, 2, 0);

        const auto vertex_path = SHADER_DIR / "vertex.vert";
        const auto fragment_path = SHADER_DIR / "fragment.frag";
        const learn::Shader shader{vertex_path, fragment_path};

        const auto brick_wall_path = TEXTURE_DIR / "wall.jpg";
        const learn::Texture brick_wall_texture{brick_wall_path};

        const auto container_path = TEXTURE_DIR / "container.jpg";
        const learn::Texture container_texture{container_path};

        const auto awesome_face_path = TEXTURE_DIR / "awesomeface.png";
        const learn::Texture awesome_face_texture{awesome_face_path};

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        while (!glfwWindowShouldClose(engine.window())) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            shader.use();
            glUniform1i(shader.uniform_location("texture0"), 0);
            glUniform1i(shader.uniform_location("texture1"), 1);

            brick_wall_texture.bind(0);
            awesome_face_texture.bind(1);

            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(engine.window());
            glfwPollEvents();
        }
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
    }
}
