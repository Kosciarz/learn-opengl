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

    private:
        GLFWwindow* m_window;
    };

} // namespace learn
