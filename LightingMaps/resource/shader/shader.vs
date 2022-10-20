#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_texture_coord;
void main()
{
    gl_Position = projection*view*model*vec4(pos, 1.0);
    frag_texture_coord = texture_coord;
    frag_normal = (model*vec4(normal,0.0)).xyz;
    frag_pos = (model*vec4(pos, 1.0)).xyz;
}
