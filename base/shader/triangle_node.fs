#version 330 core
in vec2 out_texture_coord;
out vec4 fragColor;
uniform sampler2D texture_1;

void main()
{
	fragColor = texture(texture_1, out_texture_coord);
}