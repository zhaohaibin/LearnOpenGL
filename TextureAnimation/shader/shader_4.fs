#version 330 core

in vec2 frag_texture_coord;
uniform sampler2D texture_1;
uniform sampler2D texture_2;

uniform float r;

out vec4 frag_color;
void main()
{
    vec4 color;
    float dis = distance(vec2(0,0), frag_texture_coord);
    if(dis < r)
    {
        color = texture(texture_1, frag_texture_coord);
    }else
    {
        color = texture(texture_2, frag_texture_coord);
    }
    frag_color = color;
}