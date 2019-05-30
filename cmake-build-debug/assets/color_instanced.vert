#version 330 core


layout (location = 0) in vec3 position;
layout (location = 4) in vec4 color;
layout (location = 10) in vec2 iPosition;

out vec4 vColor;

void main(void) {
	gl_Position = vec4(
	iPosition.x + position.x,
	iPosition.y + position.y,
	position.z,
	1.0);
	vColor = color;

}

