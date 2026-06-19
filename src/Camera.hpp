#pragma once

#include "InputHandler.hpp"

#include <glm/glm.hpp>

namespace learn {

    class Camera {
    public:
        explicit Camera(const glm::vec3& position = glm::vec3{0.0f, 0.0f, 3.0f},
                        const glm::vec3& up = glm::vec3{0.0f, 1.0f, 0.0f});

        [[nodiscard]] glm::mat4 view_matrix() const;
        [[nodiscard]] float fov() const { return m_fov; }

        void update(const InputState& input, const double delta_time);
        void update_vectors();

    private:
        glm::vec3 m_position;
        glm::vec3 m_right;
        glm::vec3 m_up;

        glm::vec3 m_world_up;
        glm::vec3 m_front;

        float m_yaw = -90.0f;
        float m_pitch = 0.0f;

        float m_movement_speed = 2.5f;
        float m_sensitivity = 0.01f;
        float m_fov = 45.0f;
    };

} // namespace learn
