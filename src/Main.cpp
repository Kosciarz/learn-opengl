#include "Engine.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <array>

int main() {
    learn::Engine engine;

    std::array<glm::vec2, 3> vertices{{
        {-0.5f, -0.5f},
        {0.5f, -0.5f},
        {0.0f, 0.5f},
    }};

    GLuint vao, vbo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);

    glNamedBufferData(vbo, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(glm::vec2));

    glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(vao, 0, 0);
    glEnableVertexArrayAttrib(vao, 0);

    while (!glfwWindowShouldClose(engine.window())) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 2);

        glfwSwapBuffers(engine.window());
        glfwPollEvents();
    }
}
