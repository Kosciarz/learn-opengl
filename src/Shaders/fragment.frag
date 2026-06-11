#version 460 core

in vec3 outColor;
in vec2 outTexCoord;

out vec4 FragColor;

uniform sampler2D texture0;

void main() {
    FragColor = texture(texture0, outTexCoord);
}
