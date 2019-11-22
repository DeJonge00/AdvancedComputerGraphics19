#version 410
// Geometry shader

layout(lines_adjacency) in;
layout(line_strip, max_vertices = 15​) out;

void main() {
    gl_Position = lines_adjacency[0];
    EmitVertex();
    gl_Position = lines_adjacency[2];
    EmitVertex();
    EndPrimitive();
}
