#include "InputHandler.hpp"

#include "OpenGLHeaders.hpp"

namespace learn {

    void InputHandler::update(GLFWwindow* window) {
        m_state.forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        m_state.backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
        m_state.left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
        m_state.right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    }

    void InputHandler::on_mouse_move(const double x, const double y) {
        if (m_first_mouse) {
            m_last_x = x;
            m_last_y = y;
            m_first_mouse = false;
        }

        m_state.mouse_dx = x - m_last_x;
        m_state.mouse_dy = m_last_y - y; // reversed since y-coordinates range from bottom to top
        m_last_x = x;
        m_last_y = y;
    }

    void InputHandler::on_scroll(const double dx, const double dy) {
        m_state.scroll_dx = dx;
        m_state.scroll_dy = dy;
    }

    void InputHandler::flush() {
        m_state.mouse_dx = 0.0f;
        m_state.mouse_dy = 0.0f;
        m_state.scroll_dx = 0.0f;
        m_state.scroll_dy = 0.0f;
    }

} // namespace learn
