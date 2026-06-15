#version 460 core

in vec3 outColor;
in vec2 outTexCoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    FragColor = mix(
            texture(texture0, outTexCoord),
            texture(texture1, vec2(outTexCoord.x, outTexCoord.y)),
            0.5);
}
