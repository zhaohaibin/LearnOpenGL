#version 330 core
in vec4 aColor;
out vec4 fragColor;
uniform vec3 ourColor;
void main()
{
	//fragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0);//
	fragColor = aColor;
}