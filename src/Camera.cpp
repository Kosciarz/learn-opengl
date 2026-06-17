#include "Camera.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace learn {

    Camera::Camera()
        : m_front{0.0f, 0.0f, -1.0f} {
        m_position = glm::vec3{0.0f, 0.0f, 3.0f};

        const glm::vec3 target{0.0f, 0.0f, 0.0f};
        const glm::vec3 direction = glm::normalize(m_position - target);

        const glm::vec3 world_up{0.0f, 1.0f, 0.0f};
        m_right = glm::normalize(glm::cross(world_up, direction));

        m_up = glm::cross(direction, m_right);
    }

    glm::mat4 Camera::view_matrix() const {
        return glm::lookAt(m_position, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
    }

    void Camera::process_key_input(const int key) {
        constexpr auto camera_speed = 0.05f;

        if (key == GLFW_KEY_W) {
            m_position += m_front * camera_speed;
        }
        if (key == GLFW_KEY_S) {
            m_position -= m_front * camera_speed;
        }
        if (key == GLFW_KEY_A) {
            m_position -= glm::normalize(glm::cross(m_front, m_up)) * camera_speed;
        }
        if (key == GLFW_KEY_D) {
            m_position += glm::normalize(glm::cross(m_front, m_up)) * camera_speed;
        }
    }

    void Camera::update(const glm::vec3& position) { m_position = position; }

} // namespace learn
