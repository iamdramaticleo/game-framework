#version 460

layout (location = 0) uniform vec3 u_color;

layout (location = 0) out vec4 out_color;

void main()
{
    out_color = vec4(u_color, 1.0);
}
