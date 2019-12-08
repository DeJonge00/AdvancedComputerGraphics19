#version 410

uniform int tessellation;

layout (quads) in;

in vec3 vertcoords_camera_tes[];
in vec3 vertnormal_camera_tes[];

out vec3 vertcoords_camera_fs;
out vec3 vertnormal_camera_fs;

void main(void) {
    vec4 p1 = mix(gl_in[1].gl_Position,gl_in[0].gl_Position,gl_TessCoord.x);
    vec4 p2 = mix(gl_in[2].gl_Position,gl_in[3].gl_Position,gl_TessCoord.x);
    gl_Position = mix(p1, p2, gl_TessCoord.y);
}
