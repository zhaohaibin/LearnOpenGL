#version 330 core

in vec4 pos_color;

out vec4 fragColor;
void main()
{
    fragColor = pos_color;
}