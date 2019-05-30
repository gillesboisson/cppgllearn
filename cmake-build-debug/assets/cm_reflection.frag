#version 330 core

precision highp float;

out vec4 fragColor;
in vec3 vNormal;
in vec3 vWPosition;

uniform vec3 diffuseColor;
uniform vec3 ambiantColor;
uniform vec3 specularColor;
uniform vec4 color;
uniform vec3 lightPosition;
uniform vec3 camPosition;

float specularStrength = 0.5;


struct PointLight {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

//vec3 lightDirection = vec3(-1.0,0.0,0.0);



uniform PointLight pointLight;

uniform samplerCube cubemap;

float fresnel(in vec3 eyeDirection,in vec3 normal,float scale,float bias,float power){
	return bias + scale * pow(1.0 + dot(eyeDirection, normal), power);
}

vec3 pointLightColor(
in vec3 lightPosition,
in vec3 modelPosition,
in vec3 modelNormal,
in vec3 camPosition,
in PointLight light
){
	vec3 lightDistance = modelPosition - lightPosition;
	vec3 lightDirection = normalize(lightDistance);
	vec3 viewDirection = normalize(modelPosition - camPosition);

	vec3 normal = normalize(modelNormal);
	float diff = max(dot(normal, -lightDirection), 0.0);
	vec3 diffuse = light.diffuse * diff;

	vec3 reflectDirection = reflect(lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), light.shininess);
	vec3 specular = specularStrength * spec * light.specular;

	return diffuse + specular + pointLight.ambient;
}

void main(void) {


	vec3 viewDirection = normalize(vWPosition - camPosition);
	vec3 normal = normalize(vNormal);

	float ratio = 1.00 / 2;
	vec3 I = normalize(vWPosition - camPosition);
	vec3 R = reflect(I, normal);



	fragColor =
	vec4(((1 - fresnel(viewDirection,normal,0.055,0.15,6.0)) *
	vec4(texture(cubemap, R).rgb, 1.0).rgb) + vec3(1.0),1.0)

	;



}