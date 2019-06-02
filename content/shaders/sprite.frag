
#version 330 core

precision highp float;

uniform sampler2D colorT;

in vec4 vColor;
in vec2 vUv;

out vec4 fragColor;

void main(void) {
    vec4 tColor = texture(colorT, vUv);
    float alpha = vColor.a * tColor.a;
    if(alpha == 0) discard;

    fragColor = tColor * vColor * alpha;
//    fragColor = vColor;

}