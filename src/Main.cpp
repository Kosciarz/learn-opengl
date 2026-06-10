#include "Engine.hpp"
#include "Shader.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <print>
#include <array>
#include <filesystem>

static const std::filesystem::path SHADER_DIR{SHADER_DIRECTORY};

int main() {
    try {
        learn::Engine engine;

        std::array<glm::vec2, 3> vertices{{
            {-0.5f, -0.5f},
            {0.5f, -0.5f},
            {0.0f, 0.5f},
        }};

        GLuint vao, vbo;
        glCreateVertexArrays(1, &vao);
        glCreateBuffers(1, &vbo);

        glNamedBufferData(
            vbo, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

        glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(glm::vec2));

        glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);

        glVertexArrayAttribBinding(vao, 0, 0);
        glEnableVertexArrayAttrib(vao, 0);

        const auto vertex_path = SHADER_DIR / "vertex.vert";
        const auto fragment_path = SHADER_DIR / "fragment.frag";
        const learn::Shader shader{vertex_path, fragment_path};

        while (!glfwWindowShouldClose(engine.window())) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            glfwSwapBuffers(engine.window());
            glfwPollEvents();
        }
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
    }
}
