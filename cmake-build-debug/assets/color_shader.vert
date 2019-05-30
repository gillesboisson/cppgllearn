#version 330 core


layout (location = 0) in vec3 position;
layout (location = 4) in vec4 color;
out vec4 vColor;

void main(void) {
	gl_Position = vec4(position, 1.0);
	vColor = color;

}

