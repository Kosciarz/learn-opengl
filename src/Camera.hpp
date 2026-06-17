#pragma once

#include <glm/glm.hpp>

namespace learn {

    class Camera {
    public:
        Camera();

        [[nodiscard]] glm::mat4 view_matrix() const;

        void process_key_input(const int key);

        void update(const glm::vec3& position);

    private:
        glm::vec3 m_position;
        glm::vec3 m_right;
        glm::vec3 m_up;

        glm::vec3 m_front;
    };

} // namespace learn
