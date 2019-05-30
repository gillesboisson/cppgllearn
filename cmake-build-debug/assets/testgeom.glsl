#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec4 vColor;
} gs_in[];

out vec4 fColor;

void main() {
    fColor = gs_in[0].vColor;

    gl_Position = gl_in[0].gl_Position + vec4(-0.1, -0.1, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.1, -0.1, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4( 0.1, 0.1, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}