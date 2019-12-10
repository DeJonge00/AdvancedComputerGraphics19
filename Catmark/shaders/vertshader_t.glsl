#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_world_vs;
layout (location = 1) in vec3 vertnormal_world_vs;

out vec3 vertcoords_camera_tcs;
out vec3 vertnormal_camera_tcs;

void main() {

  vertcoords_camera_tcs = vertcoords_world_vs.xyz;
  vertnormal_camera_tcs = vertnormal_world_vs.xyz;
  gl_Position = vec4(vertcoords_world_vs, 1);
}
