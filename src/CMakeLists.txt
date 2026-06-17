set(SOURCES
    "Main.cpp"
    "GLUtils.cpp"
    "Engine.cpp"
    "Shader.cpp"
    "Texture.cpp"
    "Camera.cpp"
    "stb_image_impl.cpp"
)

set(HEADERS
    "GLUtils.hpp"
    "Engine.hpp"
    "Shader.hpp"
    "Texture.hpp"
    "Camera.hpp"
)

add_executable(LearnOpenGL ${SOURCES} ${HEADERS})
target_compile_definitions(LearnOpenGL PRIVATE
    SHADER_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    TEXTURE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/textures"
)
target_link_libraries(LearnOpenGL PRIVATE
    OpenGL::GL glm::glm glfw glad stb_image
)

