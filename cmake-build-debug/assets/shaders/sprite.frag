
#version 330 core

precision highp float;

uniform sampler2D colorT;

in vec4 vColor;
in vec2 vUv;

out vec4 fragColor;

void main(void) {

    fragColor = texture(colorT, vUv) * vColor * vColor.a;
//    fragColor = vColor;

}