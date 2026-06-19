#pragma once

#include "Camera.hpp"
#include "InputHandler.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace learn {

    inline static constexpr auto WINDOW_WIDTH = 1080;
    inline static constexpr auto WINDOW_HEIGHT = 720;

    class Engine {
    public:
        Engine();
        ~Engine();

        [[nodiscard]] GLFWwindow* window() const { return m_window; }
        [[nodiscard]] Camera& camera() { return m_camera; };
        [[nodiscard]] InputHandler& input() { return m_input; }

        [[nodiscard]] int window_width() const { return m_width; }
        [[nodiscard]] int window_height() const { return m_height; }
        [[nodiscard]] float aspect_ratio() const {
            return static_cast<float>(m_width) / static_cast<float>(m_height);
        }

    private:
        static void framebuffer_size_callback(GLFWwindow* window,
                                              const int width,
                                              const int height);
        static void key_callback(GLFWwindow* window,
                                 const int key,
                                 const int scancode,
                                 const int action,
                                 const int mods);
        static void cursor_callback(GLFWwindow* window, const double x, const double y);
        static void scroll_callback(GLFWwindow* window, const double dx, const double dy);

    private:
        GLFWwindow* m_window;

        int m_width;
        int m_height;

        Camera m_camera;
        InputHandler m_input;
    };

} // namespace learn
