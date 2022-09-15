#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 color;

out vec4 aColor;

uniform vec3 ourColor;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	vec4 pos = projection * view * vec4(aPos, 1.0);
	gl_Position = pos;
	aColor = color;//vec4(ourColor.x, ourColor.y, ourColor.z, 1.0);
}