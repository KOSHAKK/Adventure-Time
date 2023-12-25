#version 460

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 texture_coords;
out vec2 t_coords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
   t_coords = texture_coords;
   gl_Position = projection * model * vec4(vertex_position, 0.f, 1.f);
}
