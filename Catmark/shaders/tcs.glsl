#version 410
in vec3 vertcoords_camera_tcs[];
in vec3 vertnormal_camera_tcs[];

out vec3 vertcoords_camera_tes[];
out vec3 vertnormal_camera_tes[];

uniform int tessellation;

layout(vertices=4) out;

void main() {
    vertcoords_camera_tes[gl_InvocationID] = vertcoords_camera_tcs[gl_InvocationID];
    vertnormal_camera_tes[gl_InvocationID] = vertnormal_camera_tcs[gl_InvocationID];

    gl_TessLevelOuter[0] = tessellation;
    gl_TessLevelOuter[1] = tessellation;
    gl_TessLevelOuter[2] = tessellation;
    gl_TessLevelInner[0] = tessellation;
}
