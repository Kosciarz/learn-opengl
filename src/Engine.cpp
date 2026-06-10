#include "Engine.hpp"
#include "GLUtils.hpp"
#include "Shader.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <print>

namespace learn {

    Engine::Engine() {
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

        m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learn OpenGL", nullptr, nullptr);
        if (!m_window) {
            throw std::runtime_error{"Failed to create window"};
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGL(glfwGetProcAddress)) {
            throw std::runtime_error{"Failed to init glad"};
        }

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        glfwSetFramebufferSizeCallback(m_window,
                                       [](GLFWwindow* window, const int width, const int height) {
                                           glViewport(0, 0, width, height);
                                       });

        glfwSetKeyCallback(m_window,
                           [](GLFWwindow* window,
                              const int key,
                              const int scancode,
                              const int action,
                              const int mods) {
                               if (action == GLFW_RELEASE && key == GLFW_KEY_ESCAPE) {
                                   glfwSetWindowShouldClose(window, true);
                               }
                           });

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(gl_utils::gl_debug_callback, nullptr);
        }
    }

    Engine::~Engine() {
        if (m_window) {
            glfwDestroyWindow(m_window);
        }

        glfwTerminate();
    }

} // namespace learn
