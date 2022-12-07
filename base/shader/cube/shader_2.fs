#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    //FragColor = texture(texture1, TexCoords);
    FragColor = vec4(0.0431, 0.0549, 0.7216, 1.0);
}