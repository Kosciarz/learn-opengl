#include "Engine.hpp"
#include "GLUtils.hpp"
#include "InputHandler.hpp"
#include "OpenGLHeaders.hpp"
#include "Cube.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <print>
#include <array>
#include <vector>

namespace learn {

    Engine::Engine()
        : m_width{WINDOW_WIDTH},
          m_height{WINDOW_HEIGHT} {
        glfwSetErrorCallback(
            [](const int error, const char* desc) { std::println("Error ({}): {}", error, desc); });

        if (!glfwInit()) {
            throw std::runtime_error{"Failed to init GLFW"};
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        m_window = glfwCreateWindow(m_width, m_height, "Learn OpenGL", nullptr, nullptr);
        if (!m_window) {
            throw std::runtime_error{"Failed to create window"};
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGL(glfwGetProcAddress)) {
            throw std::runtime_error{"Failed to init glad"};
        }

        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, Engine::framebuffer_size_callback);
        glfwSetKeyCallback(m_window, Engine::key_callback);
        glfwSetCursorPosCallback(m_window, Engine::cursor_callback);
        glfwSetScrollCallback(m_window, Engine::scroll_callback);
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glViewport(0, 0, m_width, m_height);

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(gl_utils::gl_debug_callback, nullptr);
        }
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
    }

    Engine::~Engine() {
        if (m_window) {
            glfwDestroyWindow(m_window);
        }

        glfwTerminate();
    }

    void Engine::run() {
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

        while (!glfwWindowShouldClose(m_window)) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            const double current_time = glfwGetTime();
            const double delta_time = current_time - last_time;
            last_time = current_time;

            glfwPollEvents();
            m_input.update(m_window);
            m_camera.update(m_input.state(), delta_time);
            m_input.flush();

            const glm::mat4 view = m_camera.view_matrix();
            const glm::mat4 projection =
                glm::perspective(glm::radians(m_camera.fov()), aspect_ratio(), 0.1f, 100.0f);

            for (const auto& cube : cubes) {
                cube.render(view, projection);
            }

            glfwSwapBuffers(m_window);
        }
    }

    void Engine::framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
        glViewport(0, 0, width, height);

        Engine* e = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (e) {
            e->m_width = width;
            e->m_height = height;
        }
    }

    void Engine::key_callback(
        GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    void Engine::cursor_callback(GLFWwindow* window, const double x, const double y) {
        auto* e = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (e) {
            e->m_input.on_mouse_move(x, y);
        }
    }

    void Engine::scroll_callback(GLFWwindow* window, const double dx, const double dy) {
        auto* e = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (e) {
            e->m_input.on_scroll(dx, dy);
        }
    }

} // namespace learn
