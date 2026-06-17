#pragma once

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
        [[nodiscard]] int width() const { return m_width; }
        [[nodiscard]] int height() const { return m_height; }
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

    private:
        GLFWwindow* m_window;

        int m_width;
        int m_height;
    };

} // namespace learn
