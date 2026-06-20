#include "Cube.hpp"
#include "Engine.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <print>
#include <array>
#include <vector>

int main() {
    try {
        learn::Engine engine;

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

        std::vector<learn::Cube> cubes;
        for (std::size_t i = 0; i < cube_positions.size(); ++i) {
            cubes.emplace_back(cube_positions[i], 20.0f * i);
        }

        double last_time = glfwGetTime();

        while (!glfwWindowShouldClose(engine.window())) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            const double current_time = glfwGetTime();
            const double delta_time = current_time - last_time;
            last_time = current_time;

            glfwPollEvents();
            engine.input().update(engine.window());
            engine.camera().update(engine.input().state(), delta_time);
            engine.input().flush();

            const glm::mat4 view = engine.camera().view_matrix();
            const glm::mat4 projection = glm::perspective(
                glm::radians(engine.camera().fov()), engine.aspect_ratio(), 0.1f, 100.0f);

            for (const auto& cube : cubes) {
                cube.render(view, projection);
            }

            glfwSwapBuffers(engine.window());
        }

    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
    }
}
