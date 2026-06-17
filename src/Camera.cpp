#include "Camera.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace learn {

    Camera::Camera(const glm::vec3& position)
        : m_position{position},
          m_world_up{0.0f, 1.0f, 0.0f},
          m_front{0.0f, 0.0f, -1.0f} {}

    glm::mat4 Camera::view_matrix() const {
        return glm::lookAt(m_position, m_position + m_front, m_world_up);
    }

    void Camera::process_key_input(GLFWwindow* window, const double delta_time) {
        const float camera_speed = 2.5f * static_cast<float>(delta_time);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            m_position += m_front * camera_speed;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            m_position -= m_front * camera_speed;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            m_position -= glm::normalize(glm::cross(m_front, m_up)) * camera_speed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            m_position += glm::normalize(glm::cross(m_front, m_up)) * camera_speed;
        }
    }

} // namespace learn
