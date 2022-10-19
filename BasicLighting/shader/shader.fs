#version 330 core

in vec3 frag_normal;
in vec3 frag_pos;
in vec3 obj_color;

out vec4 FragColor;

uniform vec3 light_pos;
uniform vec3 light_color;

void main()
{
    //环境光
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength*light_color;

    //计算漫反射
    vec3 norm = normalize(frag_normal);
    vec3 ligth_direction = normalize(light_pos-frag_pos);
    float diff = max(dot(norm, ligth_direction), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 result = (ambient+diffuse) * obj_color;
    FragColor = vec4(result, 1.0);
}