#version 330 core

in vec3 frag_normal;
in vec3 frag_pos;
in vec3 obj_color;

out vec4 FragColor;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 view_pos;

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

    //计算镜面高光
    float specularStrength = 0.5;
    vec3 viewDir = normalize(view_pos - frag_pos);
    //(计算反射向量)
    vec3 reflectDir = reflect(-ligth_direction, norm); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light_color;

    vec3 result = (ambient+diffuse+specular) * obj_color;
    FragColor = vec4(result, 1.0);
}