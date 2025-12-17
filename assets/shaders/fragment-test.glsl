#version 330 core

out vec4 OutColor;

in vec3 Normal;
in vec2 Uv;

struct Material {
    sampler2D diffuse;
};

struct Lighting {
    vec3 ambient;
};

uniform Material u_material;
uniform Lighting u_lighting;

void main() {
    vec3 ambient = u_lighting.ambient * texture(u_material.diffuse, Uv).rgb;
    OutColor = vec4(ambient, 1.0);
}
