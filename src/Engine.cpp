#include "Engine.hpp"
#include "GLUtils.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <print>

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

        m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learn OpenGL", nullptr, nullptr);
        if (!m_window) {
            throw std::runtime_error{"Failed to create window"};
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGL(glfwGetProcAddress)) {
            throw std::runtime_error{"Failed to init glad"};
        }

        glfwSetWindowUserPointer(m_window, this);

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        glfwSetFramebufferSizeCallback(m_window, Engine::framebuffer_size_callback);
        glfwSetKeyCallback(m_window, Engine::key_callback);

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

    void Engine::framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
        glViewport(0, 0, width, height);

        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (engine) {
            engine->m_width = width;
            engine->m_height = height;
        }
    }

    void Engine::key_callback(
        GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
        if (action != GLFW_PRESS) {
            return;
        }

        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        }

        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (engine) {
            engine->m_camera.process_key_input(key);
        }
    }

} // namespace learn
