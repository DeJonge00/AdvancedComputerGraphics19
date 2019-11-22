#version 410
// Geometry shader

layout(lines_adjacency) in;
layout(line_strip, max_vertices = 15​) out;

void main() {
    fColor = vec4(0.8, 0.5, 0.0, 1.0);
    gl_Position = lines_adjacency[0];
    EmitVertex();
    gl_Position = lines_adjacency[2];
    EmitVertex();
    EndPrimitive();
}
