#version core 330

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D screenTexture;

void main()
{
    FragColor = texture(screenTexture, TexCoords);
}