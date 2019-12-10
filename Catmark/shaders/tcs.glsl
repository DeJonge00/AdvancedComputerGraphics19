#version 410
in vec3 vertcoords_camera_tcs[];
in vec3 vertnormal_camera_tcs[];

out vec3 vertcoords_camera_tes[];
out vec3 vertnormal_camera_tes[];

uniform int inner_tessellation;
uniform int outer_tessellation;

layout(vertices=4) out;

void main() {
    vertcoords_camera_tes[gl_InvocationID] = vertcoords_camera_tcs[gl_InvocationID];
    vertnormal_camera_tes[gl_InvocationID] = vertnormal_camera_tcs[gl_InvocationID];

    if (gl_InvocationID == 0) {
        gl_TessLevelOuter[0] = outer_tessellation;
        gl_TessLevelOuter[1] = outer_tessellation;
        gl_TessLevelOuter[2] = outer_tessellation;
        gl_TessLevelOuter[3] = outer_tessellation;

        gl_TessLevelInner[0] = inner_tessellation;
        gl_TessLevelInner[1] = inner_tessellation;
    }
}
