#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 frag_normal;
out vec3 frag_pos;
out vec3 obj_color;
void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    frag_normal = (model*vec4(normal,1.0)).xyz;
    frag_pos = (model * vec4(pos, 1.0)).xyz;
    obj_color = color.rgb;
}