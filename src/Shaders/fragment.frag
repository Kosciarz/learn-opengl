#version 460 core

in vec2 outUV;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    FragColor = mix(texture(texture0, outUV), texture(texture1, outUV), 0.5);
}
