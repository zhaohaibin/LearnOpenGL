#version 330 core

uniform sampler2D texture_1;
out vec4 fragColor;
varying vec4 color;
void main()
{
    fragColor = texture(texture_1, gl_PointCoord) * color;
}