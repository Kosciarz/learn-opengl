#include "Camera.hpp"
#include "InputHandler.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace learn {

    Camera::Camera(const glm::vec3& position)
        : m_position{position},
          m_world_up{0.0f, 1.0f, 0.0f},
          m_front{0.0f, 0.0f, -1.0f} {
        m_up = m_world_up;
    }

    glm::mat4 Camera::view_matrix() const {
        return glm::lookAt(m_position, m_position + m_front, m_world_up);
    }

    void Camera::update(const InputState& input, const double delta_time) {
        const float camera_speed = 2.5f * static_cast<float>(delta_time);

        if (input.forward) {
            m_position += m_front * camera_speed;
        }
        if (input.backward) {
            m_position -= m_front * camera_speed;
        }
        if (input.left) {
            m_position -= glm::normalize(glm::cross(m_front, m_up)) * camera_speed;
        }
        if (input.right) {
            m_position += glm::normalize(glm::cross(m_front, m_up)) * camera_speed;
        }
    }

} // namespace learn
