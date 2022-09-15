#version 330 core
layout (location = 0) vec2 pos;
layout (location = 1) vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(pos.x, pos.y, 0.0, 1.0);
    TexCoords = texCoords;
}
