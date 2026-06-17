#include "Engine.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <print>
#include <array>
#include <filesystem>

static const std::filesystem::path SHADER_DIR{SHADER_DIRECTORY};
static const std::filesystem::path TEXTURE_DIR{TEXTURE_DIRECTORY};

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
};

int main() {
    try {
        learn::Engine engine;
        learn::Camera camera;

        std::array<Vertex, 24> vertices = {{
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
        std::array<unsigned int, 36> indices = {{
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
        }};
        // clang-format on

        std::array<glm::vec3, 10> cube_positions = {{
            glm::vec3{0.0f, 0.0f, 0.0f},
            glm::vec3{2.0f, 5.0f, -15.0f},
            glm::vec3{-1.5f, -2.2f, -2.5f},
            glm::vec3{-3.8f, -2.0f, -12.3f},
            glm::vec3{2.4f, -0.4f, -3.5f},
            glm::vec3{-1.7f, 3.0f, -7.5f},
            glm::vec3{1.3f, -2.0f, -2.5f},
            glm::vec3{1.5f, 2.0f, -2.5f},
            glm::vec3{1.5f, 0.2f, -1.5f},
            glm::vec3{-1.3f, 1.0f, -1.5f},
        }};

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

        // texture coordinates
        glEnableVertexArrayAttrib(vao, 1);
        glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv));
        glVertexArrayAttribBinding(vao, 1, 0);

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

        glEnable(GL_DEPTH_TEST);

        double last_time = glfwGetTime();

        while (!glfwWindowShouldClose(engine.window())) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            const double current_time = glfwGetTime();
            const double delta_time = current_time - last_time;
            last_time = current_time;

            camera.process_key_input(engine.window(), delta_time);

            const glm::mat4 view = camera.view_matrix();

            const glm::mat4 projection =
                glm::perspective(glm::radians(45.0f), engine.aspect_ratio(), 0.1f, 100.0f);

            for (int i = 0; i < cube_positions.size(); ++i) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cube_positions[i]);
                const float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3{1.0f, 0.3f, 0.5f});

                // drawing
                {
                    shader.use();
                    glUniform1i(shader.uniform_location("texture0"), 0);
                    glUniform1i(shader.uniform_location("texture1"), 1);

                    glUniformMatrix4fv(
                        shader.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
                    glUniformMatrix4fv(
                        shader.uniform_location("view"), 1, GL_FALSE, glm::value_ptr(view));
                    glUniformMatrix4fv(shader.uniform_location("projection"),
                                       1,
                                       GL_FALSE,
                                       glm::value_ptr(projection));

                    brick_wall_texture.bind(0);
                    awesome_face_texture.bind(1);

                    glBindVertexArray(vao);
                    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
                }
            }

            glfwSwapBuffers(engine.window());
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
    }
}
