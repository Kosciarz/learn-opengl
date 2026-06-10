#pragma once

#include <glad/gl.h>

namespace gl_utils {

    void gl_debug_callback(GLenum source,
                           GLenum type,
                           GLuint id,
                           GLenum severity,
                           GLsizei length,
                           const GLchar* message,
                           const void* userParam);

} // namespace gl_utils
