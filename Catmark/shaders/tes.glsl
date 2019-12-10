#version 410
layout (quads, equal_spacing, cw) in;

in vec3 vertcoords_camera_tes[];
in vec3 vertnormal_camera_tes[];

out vec3 vertcoords_camera_fs;
out vec3 vertnormal_camera_fs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;

vec3 interpolate(vec3 c0, vec3 c1, vec3 c2, vec3 c3, float w1, float w2) {
    vec3 p1 = mix(c1 ,c0, w1);
    vec3 p2 = mix(c2, c3, w1);
    return mix(p1, p2, w2);
}

void main(void) {
    float x = gl_TessCoord.x;
    float y = gl_TessCoord.y;

    vec3 c0 = vertcoords_camera_tes[0];
    vec3 c1 = vertcoords_camera_tes[1];
    vec3 c2 = vertcoords_camera_tes[2];
    vec3 c3 = vertcoords_camera_tes[3];

    vec4 coords_avg = vec4(interpolate(c0, c1, c2, c3, x, y), 1);
    vertcoords_camera_fs = normalize(normalmatrix * vec3(projectionmatrix * modelviewmatrix * coords_avg));

    vec3 n0 = vertnormal_camera_tes[0];
    vec3 n1 = vertnormal_camera_tes[1];
    vec3 n2 = vertnormal_camera_tes[2];
    vec3 n3 = vertnormal_camera_tes[3];

    vec4 normal_avg = vec4(interpolate(n0, n1, n2, n3, x, y), 1);
    vertnormal_camera_fs = normalize(normalmatrix * vec3(projectionmatrix * modelviewmatrix * normal_avg));
}
