#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture_1;

void main()
{
    FragColor = texture(texture_1, TexCoords);
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}