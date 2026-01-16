#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;

out vec3 Normal;
out vec2 Uv;
out vec3 Position;

uniform mat4 u_mvp;
uniform mat4 u_model;
uniform mat3 u_normal;

void main() {
    gl_Position = u_mvp * vec4(aPosition, 1.0);
    Uv = aUv;
    Normal = u_normal * aNormal;
    Position = vec3(u_model * vec4(aPosition, 1.0));
}
