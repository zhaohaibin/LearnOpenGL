#version 330 core

uniform sampler2D texture_1;

in vec2 frag_texture_coord;
out vec4 color;
void main()
{
    color = texture(texture_1, frag_texture_coord);
}