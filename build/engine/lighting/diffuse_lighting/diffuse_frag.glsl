#version 460

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

layout (location = 0) out vec4 out_color;

layout (binding = 1, std140) uniform u_material
{
    vec3 diffuse;
}
material;

layout (binding = 2, std140) uniform u_light
{
    vec3  position;
    float ambient;
    vec3  color;
}
light;

void main()
{
    vec3 normal          = normalize(in_normal);
    vec3 light_direction = normalize(light.position - in_position);

    vec3 ambient_color   = light.color * light.ambient;

    float diffuse_factor = max(dot(normal, light_direction), 0.0);
    vec3  diffuse_color  = diffuse_factor * light.color;

    vec3 color = (ambient_color + diffuse_color) * material.diffuse;
     out_color = vec4(color, 1.0);
}