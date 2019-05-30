#version 330 core

layout (location = 0) in vec2 position;

out vec2 vPosition;

void main(void) {

    vPosition = position + vec2(2.0,1.0);

}

