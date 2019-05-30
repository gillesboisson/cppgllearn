#version 330 core


layout (location = 0) in vec3 position;
layout (location = 3) in vec3 normal;

out vec3 vNormal;
out vec3 vWPosition;


struct Transform {
	mat4 mvp;
	mat4 rot;
	mat4 m;
};

layout (std140) uniform TransformUB {
	Transform transform;
};

void main(void) {
	gl_Position = transform.mvp * vec4(position, 1.0);
	vWPosition 	= (transform.m * vec4(position,1.0)).xyz;
	vNormal 	= (transform.rot * vec4(normal,1.0)).xyz;

}

