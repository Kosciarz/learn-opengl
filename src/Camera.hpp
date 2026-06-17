#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace learn {

    class Camera {
    public:
        Camera(const glm::vec3& position = glm::vec3{0.0f, 0.0f, 3.0f});

        [[nodiscard]] glm::mat4 view_matrix() const;

        void process_key_input(GLFWwindow* window, const double delta_time);

    private:
        glm::vec3 m_position;
        glm::vec3 m_right;
        glm::vec3 m_up;

        glm::vec3 m_world_up;
        glm::vec3 m_front;
    };

} // namespace learn
