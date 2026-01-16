#version 330 core

out vec4 OutColor;

in vec3 Normal;
in vec2 Uv;
in vec3 Position;

struct Material {
    sampler2D diffuse;
    vec3 specularColor;
    float specularStrength;
    float shininess;
};

struct Lighting {
    vec3 ambient;
    vec3 sunPosition;
    vec3 sunColor;
};

uniform Material u_material;
uniform Lighting u_lighting;
uniform vec3 u_cameraPos;

void main() {
    vec3 normal   = normalize(Normal);
    vec3 lightDir = normalize(u_lighting.sunPosition - Position);
    vec3 viewDir  = normalize(u_cameraPos - Position);

    vec3 halfwayDir  = normalize(lightDir + viewDir);
    float specFactor = pow(max(dot(normal, halfwayDir), 0.0), u_material.shininess);

    vec3 specular = u_material.specularColor * u_material.specularStrength * u_lighting.sunColor * specFactor;
    vec3 ambient  = u_lighting.ambient;
    vec3 diffuse  = max(dot(normal, lightDir), 0.0) * u_lighting.sunColor;

    vec3 result = (ambient + diffuse) * texture(u_material.diffuse, Uv).rgb + specular;
    OutColor = vec4(result, 1.0);
}
