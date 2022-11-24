#version 330 core


uniform sampler2D texture_1;
in vec2 frag_texture_coord;
out vec4 fragColor;
void main()
{
    fragColor = texture(texture_1, frag_texture_coord);

    if(fragColor.a < 0.1)
        discard;
}