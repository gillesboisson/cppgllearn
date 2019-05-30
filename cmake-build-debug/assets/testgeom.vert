#version 330 core


layout (location = 0) in vec3 position;
layout (location = 4) in vec4 color;


//out vec4 vColor;

out VS_OUT {
	vec4 vColor;
} vs_out;

void main(void) {
	gl_Position = vec4(position, 1.0);
	vs_out.vColor = color;

}

