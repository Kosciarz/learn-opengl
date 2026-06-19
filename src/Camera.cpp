#include "Camera.hpp"
#include "InputHandler.hpp"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <cmath>

namespace learn {

    Camera::Camera(const glm::vec3& position, const glm::vec3& up)
        : m_position{position},
          m_up{up},
          m_world_up{up},
          m_front{0.0f, 0.0f, -1.0f} {
        update_vectors();
    }

    glm::mat4 Camera::view_matrix() const {
        return glm::lookAt(m_position, m_position + m_front, m_world_up);
    }

    void Camera::update(const InputState& input, const double delta_time) {
        const auto dt = static_cast<float>(delta_time);

        if (input.forward) {
            m_position += m_front * m_movement_speed * dt;
        }
        if (input.backward) {
            m_position -= m_front * m_movement_speed * dt;
        }
        if (input.left) {
            m_position -= m_right * m_movement_speed * dt;
        }
        if (input.right) {
            m_position += m_right * m_movement_speed * dt;
        }

        m_yaw += input.mouse_dx * m_sensitivity;
        m_pitch += input.mouse_dy * m_sensitivity;
        m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

        update_vectors();

        m_fov -= input.scroll_dy;
        m_fov = glm::clamp(m_fov, 1.0f, 90.0f);
    }

    void Camera::update_vectors() {
        glm::vec3 front;
        front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
        front.y = std::sin(glm::radians(m_pitch));
        front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);

        m_right = glm::normalize(glm::cross(m_front, m_world_up));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }

} // namespace learn
