#version 410
layout (location = 0) in vec3 vertcoords_camera_tcs[];
layout (location = 1) in vec3 vertnormal_camera_tcs[];

layout (location = 0) out vec3 vertcoords_camera_tec[];
layout (location = 1) out vec3 vertnormal_camera_tec[];

void main() {
    vertcoords_camera_tec[gl_InvocationID].gl_Position = vertcoords_camera_tcs[gl_InvocationID].gl_Position;
    vertnormal_camera_tec[gl_InvocationID].gl_Position = vertnormal_camera_tcs[gl_InvocationID].gl_Position;
}
