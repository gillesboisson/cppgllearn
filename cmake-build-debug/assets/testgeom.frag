#version 330 core

precision highp float;

in vec4 fColor;
out vec4 fragColor;

void main(void) {

	fragColor = fColor;
}