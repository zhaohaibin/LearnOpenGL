#version 440 core

layout(location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec4 color;
void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    gl_PointSize = 32;
    color = vec4(0.3, 0.6, 0.1,0.3);
}