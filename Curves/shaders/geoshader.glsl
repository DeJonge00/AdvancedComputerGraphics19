#version 410
// Geometry shader
uniform bool combs;

layout(lines_adjacency) in;

layout(line_strip, max_vertices = 64) out;
out vec4 gColor;

void main() {
    gColor = vec4(0.8, 0.0, 0.0, 1.0);
    if (true) {
       gColor = vec4(0.8, 0.5, 0.0, 1.0);
    }
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();

    if (true) {
        float x1 = gl_in[1].gl_Position.x;
        float y1 = gl_in[1].gl_Position.y;
        float x2 = gl_in[2].gl_Position.x;
        float y2 = gl_in[2].gl_Position.y;
        float x3 = gl_in[3].gl_Position.x;
        float y3 = gl_in[3].gl_Position.y;

        float A = x1 * (y2-y3) - y1 * (x2-x3) + x2*y3 -x3*y2;
        float B = (x1*x1 + y1*y1) * (y3-y2) + (x2*x2 + y2*y2) * (y1-y3) + (x3*x3 + y3*y3) * (y2-y1);
        float C = (x1*x1 + y1*y1) * (x2-x3) + (x2*x2 + y2*y2) * (x3-x1) + (x3*x3 + y3*y3) * (x1-x2);

        float x = - (B / (2*A));
        float y = - (C / (2*A));

        gl_Position = gl_in[2].gl_Position;
        EmitVertex();

        gl_Position = vec4(x, y, 0, 1);
        EmitVertex();
        EndPrimitive();
    }

}
