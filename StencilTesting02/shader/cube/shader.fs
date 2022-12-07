#version 330 core

in vec2 frag_texture_coord;

uniform sampler2D texture_1;

out vec4 color;

void main()
{
    color = texture(texture_1, frag_texture_coord);
}