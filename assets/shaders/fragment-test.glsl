#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec2 Uv;

struct Material {
    sampler2D diffuse;
};

uniform Material u_material;

void main() {
    FragColor = texture(u_material.diffuse, Uv);
}
