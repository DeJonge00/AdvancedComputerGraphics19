#version 410
// Geometry shader

layout(lines_adjacency) in;
layout(lines, max_vertices = 2) out;

void main() {

    gl_Position = gl_PositionIn[0];
    EmitVertex();
    gl_Position = gl_PositionIn[3] + vec4(0.0, 1.0, 0.0, 1.0); ;
    EmitVertex();


    EndPrimitive();
}
