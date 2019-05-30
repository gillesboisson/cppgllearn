#version 330 core

layout (location = 0) in vec3 position;



uniform mat4 mvp;
uniform mat4 camRot;

out vec3 vPosition;

void main(void) {

	gl_Position = mvp * vec4(position, 1.0);
	vPosition = (camRot * vec4(position.x,-position.y,position.z,1.0)).xyz;

}

