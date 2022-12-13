#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texture_coord;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec3 bitangent;
layout (location = 4) in vec3 normal;

out vec2 frag_texture_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT
{
    vec3 pos;
    vec2 texture_coord;
    mat3 TBN;
} vs_out;

void main()
{
    //计算世界坐标下的TBN
    vec3 T = normalize(vec3(model*vec4(tangent, 0.0)));
    vec3 B = normalize(vec3(model* vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3(model* vec4(normal, 0.0)));
    mat3 TBN = mat3(T,B,N);

    vs_out.pos = (model * vec4(pos, 1.0)).xyz;
    vs_out.texture_coord = texture_coord;
    vs_out.TBN = TBN;
    gl_Position = projection * view * model * vec4(pos, 1.0);
    frag_texture_coord = texture_coord;
}