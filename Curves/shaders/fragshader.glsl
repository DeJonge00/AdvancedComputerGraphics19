#version 410
// Fragment shader

in vec4 gColor;
out vec4 fColor;

void main() {

  if (gColor.xyz == vec3(0)) {
      fColor = vec4(0.8, 0.0, 0.0, 1.0);
  } else {
      fColor = gColor;
  }
}
