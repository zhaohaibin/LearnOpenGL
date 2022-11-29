#version 330 core

out vec4 fragColor;

uniform vec3 offset;
uniform sampler2D texture_1;

in vec2 frag_texture_coord;
void main()
{
    fragColor = texture(texture_1, vec2(frag_texture_coord.x +offset.x,  frag_texture_coord.y + offset.y));
}