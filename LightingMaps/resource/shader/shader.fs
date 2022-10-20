#version 330 core

in vec2 frag_texture_coord;

uniform vec3 light;
uniform vec3 light_pos;
uniform sampler2D diffuse;
uniform sampler2D specular;
uniform vec3 view_pos; 

in vec3 frag_normal;
in vec3 frag_pos;

out vec4 frag_color;
void main()
{
    //计算环境光
    float ambient_strength = 0.5;
    vec3 ambient = ambient_strength*light;
    ambient = ambient*(texture(diffuse, frag_texture_coord)).rgb;
    
    //计算漫反射
    vec3 light_direction = normalize(light_pos - frag_pos);
    vec3 norm = normalize(frag_normal);
    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = diff*(texture(diffuse, frag_texture_coord)).rgb*light;

    //计算镜面高光
    vec3 viewDir = normalize(view_pos - frag_pos);

    //计算光线的反射方向向量
    vec3 reflectDir = reflect(-light_direction, norm);
    //计算高亮点大小当前设置为32数值越大两点越小亮度越高
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);

    vec3 specular = light * spec * texture(specular, frag_texture_coord).rgb; 

    frag_color = vec4(ambient+diffuse+specular, 1.0);
}