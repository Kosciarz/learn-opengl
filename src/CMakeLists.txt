set(SOURCES
    "Main.cpp"
    "GLUtils.hpp"
    "GLUtils.cpp"
    "Shader.hpp"
    "Shader.cpp"
)

add_executable(LearnOpenGL ${SOURCES})
target_compile_definitions(LearnOpenGL
    PRIVATE SHADER_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/Shaders"
)
target_link_libraries(LearnOpenGL
    PRIVATE OpenGL::GL glm::glm glfw glad
)

