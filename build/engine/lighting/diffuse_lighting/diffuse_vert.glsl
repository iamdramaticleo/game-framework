#version 460

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;

layout (location = 0) uniform mat4    u_model;
layout (binding  = 0, std140) uniform u_camera
{
    mat4 view;
    mat4 proj;
}
camera;

void main()
{
    out_position = vec3(u_model  * vec4(in_position, 1.0));
    out_normal   = mat3(u_model) * in_normal;

    gl_Position  = camera.proj * camera.view * vec4(out_position, 1.0);
}
