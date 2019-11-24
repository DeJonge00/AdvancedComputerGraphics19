#version 410
// Geometry shader
uniform bool combs;
uniform bool circle;
uniform int selected_circle;

layout(lines_adjacency) in;

layout(line_strip, max_vertices = 64) out;
out vec4 gColor;

#define PI 3.1415926

void draw(vec4 v1, vec4 v2, vec4 v3) {
    float x1 = v1.x;
    float y1 = v1.y;
    float x2 = v2.x;
    float y2 = v2.y;
    float x3 = v3.x;
    float y3 = v3.y;

    float A = x1 * (y2-y3) - y1 * (x2-x3) + x2*y3 -x3*y2;
    float B = (x1*x1 + y1*y1) * (y3-y2) + (x2*x2 + y2*y2) * (y1-y3) + (x3*x3 + y3*y3) * (y2-y1);
    float C = (x1*x1 + y1*y1) * (x2-x3) + (x2*x2 + y2*y2) * (x3-x1) + (x3*x3 + y3*y3) * (x1-x2);

    float x = - (B / (2*A));
    float y = - (C / (2*A));

    if (true) {
        gl_Position = v2;
        EmitVertex();

        gl_Position = vec4(x, y, 0, 1);
        EmitVertex();
        EndPrimitive();
    }

    if (true && gl_PrimitiveIDIn == 2) {
        int circle_points = 30;
        float D = (x1*x1 + y1*y1) * (x3*y2-x2*y3) + (x2*x2 + y2*y2) * (x1*y3 - x3*y1) + (x3*x3 + y3*y3) * (x2*y1 - x1*y2);
        float r = sqrt((B*B + C*C - 4*A*D) / (4*A*A));

        for(int i = 0; i <= circle_points; i++) {
            gl_Position = vec4(x, y, 0, 1) + r*vec4(cos((2*PI*i)/circle_points), sin((2*PI*i)/circle_points), 0, 0);
            EmitVertex();
        }
    }
}

void main() {
    if (true) {
       gColor = vec4(0.8, 0.5, 0.0, 1.0);
    }
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();

    if (combs || true) {
        if (gl_PrimitiveIDIn == 0) {
            draw(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);
        }
        draw(gl_in[1].gl_Position, gl_in[2].gl_Position, gl_in[3].gl_Position);
    }
}
