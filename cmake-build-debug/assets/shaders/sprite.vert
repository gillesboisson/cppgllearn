#version 330 core

uniform mat4 vp;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 4) in vec4 color;

//uniform mat4 mvp;

out vec4 vColor;
out vec2 vUv;

void main(void) {
    vColor = color;
    vUv = uv;

    gl_Position = vp * vec4(position, 1.0);
}