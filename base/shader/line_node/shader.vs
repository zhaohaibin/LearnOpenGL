#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

out vec4 pos_color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection*view*model*vec4(pos.x, pos.y, pos.z, 1.0);
    pos_color = color;
}