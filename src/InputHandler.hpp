#pragma once

#include "OpenGLHeaders.hpp"

namespace learn {

    struct InputState {
        // movement
        bool forward = false;
        bool backward = false;
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;

        // mouse
        float mouse_dx = 0.0f;
        float mouse_dy = 0.0f;
        float scroll_dx = 0.0f;
        float scroll_dy = 0.0f;
    };

    class InputHandler {
    public:
        void update(GLFWwindow* window);
        void on_mouse_move(const double x, const double y);
        void on_scroll(const double dx, const double dy);
        void flush();

        [[nodiscard]] const InputState& state() const { return m_state; }

    private:
        InputState m_state;

        float m_last_x = 0.0f;
        float m_last_y = 0.0f;
        bool m_first_mouse = true;
    };

} // namespace learn
