#include "Engine.hpp"
#include "Shader.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <print>
#include <array>
#include <filesystem>

static const std::filesystem::path SHADER_DIR{SHADER_DIRECTORY};

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

int main() {
    try {
        learn::Engine engine;

        std::array<Vertex, 4> vertices{{
            {.position = {-0.5f, -0.5f, 0.0f}, .color = {1.0f, 0.0f, 0.0f}},
            {.position = {0.5f, -0.5f, 0.0f}, .color = {0.0f, 1.0f, 0.0f}},
            {.position = {0.5f, 0.5f, 0.0f}, .color = {0.0f, 0.0f, 1.0f}},
            {.position = {-0.5f, 0.5f, 0.0f}, .color = {1.0f, 0.0f, 1.0f}},
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
        glEnableVertexArrayAttrib(vao, 0);
        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
        glVertexArrayAttribBinding(vao, 0, 0);

        glEnableVertexArrayAttrib(vao, 1);
        glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
        glVertexArrayAttribBinding(vao, 1, 0);

        const auto vertex_path = SHADER_DIR / "vertex.vert";
        const auto fragment_path = SHADER_DIR / "fragment.frag";
        const learn::Shader shader{vertex_path, fragment_path};

        while (!glfwWindowShouldClose(engine.window())) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(engine.window());
            glfwPollEvents();
        }
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
    }
}
