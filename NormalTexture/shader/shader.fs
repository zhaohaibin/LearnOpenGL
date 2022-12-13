#version 330 core
in vec2 frag_texture_coord;

in VS_OUT
{
    vec3 pos;
    vec2 texture_coord;
    mat3 TBN;
} fs_in;

uniform sampler2D texture_normal;
uniform sampler2D texture_1;
uniform vec3 light_pos;
uniform vec3 view_pos;
uniform vec3 light;


out vec4 color;
void main()
{
    //基于TBN计算法线
    vec3 normal = texture(texture_normal, fs_in.texture_coord).rgb;
    normal = normalize(normal*2.0-1.0);
    normal = normalize(fs_in.TBN*normal);

    //基于法线计算光照

    //计算环境光
    float ambient_strength = 0.5;
    vec3 ambient = ambient_strength*light;
    ambient = ambient*(texture(texture_1, fs_in.texture_coord).rgb);

    //计算漫反射
    vec3 light_direction = normalize(light_pos - fs_in.pos);
    float diff = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = diff*(texture(texture_1, fs_in.texture_coord)).rgb*light;

    //计算镜面高光
    vec3 viewDir = normalize(view_pos - fs_in.pos);

    //计算光线的反射方向向量
    vec3 reflectDir = reflect(-light_direction, normal);
    //计算高亮点大小当前设置为32数值越大两点越小亮度越高
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);

    vec3 specular = light * spec * texture(texture_1, fs_in.texture_coord).rgb; 

    color = vec4(ambient+diffuse+specular, 1.0);
    //color = vec4(normal, 1.0);
    //color = texture(texture_1, frag_texture_coord);
}