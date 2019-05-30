#version 330 core

precision highp float;


out vec4 fragColor;
uniform samplerCube cubemap;
in vec3 vPosition;

void main(void) {

//	vec3 normal = normalize(vPosition);

	fragColor = texture(cubemap, vPosition);;
}