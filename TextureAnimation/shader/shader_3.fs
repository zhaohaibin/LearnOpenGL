#version 330 core

in vec2 frag_texture_coord;
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform vec3 offset;

out vec4 frag_color;
void main()
{
    vec4 color;
    if(frag_texture_coord.x < offset.x)
    {
        color = texture(texture_1, frag_texture_coord);
    }else
    {
        color = texture(texture_2, frag_texture_coord);
    }
    frag_color = color;
}