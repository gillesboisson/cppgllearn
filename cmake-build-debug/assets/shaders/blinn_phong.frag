#version 330 core

precision highp float;

out vec4 fragColor;
in vec3 vNormal;
in vec3 vWPosition;


uniform vec4 color;
uniform vec3 camPosition;

float specularStrength = 0.5;

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    float shininess;
};

//vec3 lightDirection = vec3(-1.0,0.0,0.0);

layout (std140) uniform Light {
    PointLight pointLight;
};

vec3 pointLightColor(
in vec3 modelPosition,
in vec3 modelNormal,
in vec3 camPosition,
in PointLight light
){
    vec3 lightDistance = modelPosition - light.position;
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

vec3 blinnPhong(
in vec3 modelPosition,
in vec3 modelNormal,
in vec3 camPosition,
in PointLight light
){

    vec3 lightDir   = normalize(modelPosition - light.position);
    vec3 viewDir    = normalize(camPosition - modelPosition);
//    vec3 halfwayDir = normalize(lightDir + viewDir);

    vec3 normal = normalize(modelNormal);

    float diff = max(dot(normal, -lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff;

//    vec3 reflectDirection = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDirection), 0.0), 8.0);


    vec3 halfwayDir = normalize(- lightDir - viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);

    vec3 specular = specularStrength * spec * light.specular;

//    float spec = pow(max(dot(normal, halfwayDir), 0.0), 16);
//    vec3 specular = light.specular * spec;

    return diffuse + specular + pointLight.ambient;

}

void main(void) {
    fragColor = vec4(blinnPhong(vWPosition, vNormal, camPosition, pointLight), 1.0) * color;
}