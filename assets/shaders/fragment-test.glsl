#version 330 core

out vec4 FragColor;

in vec2 Uv;
in vec3 Normal;

struct Material {
    sampler2D diffuse;
};

uniform Material u_material;

void main() {
    FragColor = texture(u_material.diffuse, Uv);
}
