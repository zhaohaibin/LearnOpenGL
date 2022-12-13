#include "normal_texture_node.h"
#include "..\base\geometry_node.h"
#include "..\base\system_env.h"
#include "../base/camera.h"

normal_texture_node::normal_texture_node()
{
	add_child(create_node());
	add_child(create_node_2());
}

node* normal_texture_node::create_node()
{
	float data[18] = {
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,

		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};
	float* vertex_data = new float[sizeof(data) / sizeof(float)];
	memcpy(vertex_data, data, sizeof(data));
	geometry_node* p = new geometry_node;	
	p->set_vertex(vertex_data, sizeof(data), 0);


	float textrue_coord_array[12] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};
	float * texture_coord_data = new float[sizeof(textrue_coord_array) / sizeof(float)];
	memcpy(texture_coord_data, textrue_coord_array, sizeof(textrue_coord_array));
	p->set_vertex_texture(texture_coord_data, sizeof(textrue_coord_array), 1);

	shader_file _file;
	_file.m_vertex_shader_file = "./shader/shader.vs";
	_file.m_frag_shader_file = "./shader/shader.fs";
	p->create_shader(_file);

	p->add_material("texture_1", "./shader/brickwall.jpg");
	p->add_material("texture_normal", "./shader/brickwall_normal.jpg");

	glm::vec3 pos = system_env::instance()->get_camera()->get_position();
	p->set_shader_value("view_pos", pos);

	glm::vec3 light_pos = glm::vec3(0.0, 0.0, 2.0);
	p->set_shader_value("light_pos", light_pos);

	glm::vec3 light(1.0, 1.0, 1.0);
	p->set_shader_value("light", light);

	//计算TBN
	glm::vec3 pos_1(data[0], data[1], data[2]);
	glm::vec3 pos_2(data[3], data[4], data[5]);
	glm::vec3 pos_3(data[6], data[7], data[8]);
	glm::vec2 uv_1(textrue_coord_array[0], textrue_coord_array[1]);
	glm::vec2 uv_2(textrue_coord_array[2], textrue_coord_array[3]);
	glm::vec2 uv_3(textrue_coord_array[4], textrue_coord_array[5]);
	glm::vec3 tangent, bitangent, normal;
	calculate_tbn(pos_1, pos_2, pos_3, uv_1, uv_2, uv_3, tangent, bitangent, normal);

	glm::vec3 pos_4(data[9], data[10], data[11]);
	glm::vec3 pos_5(data[12], data[13], data[14]);
	glm::vec3 pos_6(data[15], data[16], data[17]);
	glm::vec2 uv_4(textrue_coord_array[6], textrue_coord_array[7]);
	glm::vec2 uv_5(textrue_coord_array[8], textrue_coord_array[9]);
	glm::vec2 uv_6(textrue_coord_array[10], textrue_coord_array[11]);
	glm::vec3 tangent_2, bitangent_2, normal_2;
	calculate_tbn(pos_4, pos_5, pos_6, uv_4, uv_5, uv_6, tangent_2, bitangent_2, normal_2);

	//构建TBN数组
	float tangent_data[18] =
	{
		tangent.x, tangent.y, tangent.z,
		tangent.x, tangent.y, tangent.z,
		tangent.x, tangent.y, tangent.z,
		tangent_2.x, tangent_2.y, tangent_2.z,
		tangent_2.x, tangent_2.y, tangent_2.z,
		tangent_2.x, tangent_2.y, tangent_2.z
	};
	float* p_tangent = new float[18];
	memcpy(p_tangent, tangent_data, sizeof(tangent_data));
	p->set_layout_data(p_tangent, sizeof(tangent_data), 2, 3);
	float bitangent_data[18] =
	{
		bitangent.x, bitangent.y, bitangent.z,
		bitangent.x, bitangent.y, bitangent.z,
		bitangent.x, bitangent.y, bitangent.z,
		bitangent_2.x, bitangent_2.y, bitangent_2.z,
		bitangent_2.x, bitangent_2.y, bitangent_2.z,
		bitangent_2.x, bitangent_2.y, bitangent_2.z
	};
	float* p_bitangent = new float[18];
	memcpy(p_bitangent, bitangent_data, sizeof(bitangent_data));
	p->set_layout_data(p_bitangent, sizeof(bitangent_data), 3, 3);
	float normal_data[18] =
	{
		normal.x, normal.y, normal.z,
		normal.x, normal.y, normal.z,
		normal.x, normal.y, normal.z,
		normal_2.x, normal_2.y, normal_2.z,
		normal_2.x, normal_2.y, normal_2.z,
		normal_2.x, normal_2.y, normal_2.z
	};
	float* p_normal = new float[18];
	memcpy(p_normal, normal_data, sizeof(normal_data));
	p->set_layout_data(p_normal, sizeof(normal_data), 4, 3);
	return p;
}

node* normal_texture_node::create_node_2()
{
	float data[18] = {
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f
	};
	float* vertex_data = new float[sizeof(data) / sizeof(float)];
	memcpy(vertex_data, data, sizeof(data));
	geometry_node* p = new geometry_node;
	p->set_vertex(vertex_data, sizeof(data), 0);


	float textrue_coord_array[12] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};
	float * texture_coord_data = new float[sizeof(textrue_coord_array) / sizeof(float)];
	memcpy(texture_coord_data, textrue_coord_array, sizeof(textrue_coord_array));
	p->set_vertex_texture(texture_coord_data, sizeof(textrue_coord_array), 1);

	shader_file _file;
	_file.m_vertex_shader_file = "./shader/shader.vs";
	_file.m_frag_shader_file = "./shader/shader.fs";
	p->create_shader(_file);

	p->add_material("texture_1", "./shader/brickwall.jpg");
	p->add_material("texture_normal", "./shader/brickwall_normal.jpg");

	glm::vec3 pos = system_env::instance()->get_camera()->get_position();
	p->set_shader_value("view_pos", pos);

	glm::vec3 light_pos = glm::vec3(0.0, 0.0, 2.0);
	p->set_shader_value("light_pos", light_pos);

	glm::vec3 light(1.0, 1.0, 1.0);
	p->set_shader_value("light", light);

	//计算TBN
	glm::vec3 pos_1(data[0], data[1], data[2]);
	glm::vec3 pos_2(data[3], data[4], data[5]);
	glm::vec3 pos_3(data[6], data[7], data[8]);
	glm::vec2 uv_1(textrue_coord_array[0], textrue_coord_array[1]);
	glm::vec2 uv_2(textrue_coord_array[2], textrue_coord_array[3]);
	glm::vec2 uv_3(textrue_coord_array[4], textrue_coord_array[5]);
	glm::vec3 tangent, bitangent, normal;
	calculate_tbn(pos_1, pos_2, pos_3, uv_1, uv_2, uv_3, tangent, bitangent, normal);

	glm::vec3 pos_4(data[9], data[10], data[11]);
	glm::vec3 pos_5(data[12], data[13], data[14]);
	glm::vec3 pos_6(data[15], data[16], data[17]);
	glm::vec2 uv_4(textrue_coord_array[6], textrue_coord_array[7]);
	glm::vec2 uv_5(textrue_coord_array[8], textrue_coord_array[9]);
	glm::vec2 uv_6(textrue_coord_array[10], textrue_coord_array[11]);
	glm::vec3 tangent_2, bitangent_2, normal_2;
	calculate_tbn(pos_4, pos_5, pos_6, uv_4, uv_5, uv_6, tangent_2, bitangent_2, normal_2);

	//构建TBN数组
	float tangent_data[18] =
	{
		tangent.x, tangent.y, tangent.z,
		tangent.x, tangent.y, tangent.z,
		tangent.x, tangent.y, tangent.z,
		tangent_2.x, tangent_2.y, tangent_2.z,
		tangent_2.x, tangent_2.y, tangent_2.z,
		tangent_2.x, tangent_2.y, tangent_2.z
	};
	float* p_tangent = new float[18];
	memcpy(p_tangent, tangent_data, sizeof(tangent_data));
	p->set_layout_data(p_tangent, sizeof(tangent_data), 2, 3);
	float bitangent_data[18] =
	{
		bitangent.x, bitangent.y, bitangent.z,
		bitangent.x, bitangent.y, bitangent.z,
		bitangent.x, bitangent.y, bitangent.z,
		bitangent_2.x, bitangent_2.y, bitangent_2.z,
		bitangent_2.x, bitangent_2.y, bitangent_2.z,
		bitangent_2.x, bitangent_2.y, bitangent_2.z
	};
	float* p_bitangent = new float[18];
	memcpy(p_bitangent, bitangent_data, sizeof(bitangent_data));
	p->set_layout_data(p_bitangent, sizeof(bitangent_data), 3, 3);
	float normal_data[18] =
	{
		normal.x, normal.y, normal.z,
		normal.x, normal.y, normal.z,
		normal.x, normal.y, normal.z,
		normal_2.x, normal_2.y, normal_2.z,
		normal_2.x, normal_2.y, normal_2.z,
		normal_2.x, normal_2.y, normal_2.z
	};
	float* p_normal = new float[18];
	memcpy(p_normal, normal_data, sizeof(normal_data));
	p->set_layout_data(p_normal, sizeof(normal_data), 4, 3);
	return p;
}

void normal_texture_node::calculate_tbn(
	const glm::vec3& pos_1, const glm::vec3& pos_2, const glm::vec3& pos_3, 
	const glm::vec2& uv_1, const glm::vec2& uv_2, const glm::vec2& uv_3, 
	glm::vec3& tangent, glm::vec3& bitangent, glm::vec3& normal)
{
	glm::vec3 edge_1 = pos_2 - pos_1;
	glm::vec3 edge_2 = pos_3 - pos_1;
	glm::vec2 deltaUV_1 = uv_2 - uv_1;
	glm::vec2 deltaUV_2 = uv_3 - uv_1;

	float f = 1.0f / (deltaUV_1.x * deltaUV_2.y - deltaUV_2.x* deltaUV_1.y);

	tangent.x = f * (deltaUV_2.y * edge_1.x - deltaUV_1.y * edge_2.x);
	tangent.y = f * (deltaUV_2.y * edge_1.y - deltaUV_1.y * edge_2.y);
	tangent.z = f * (deltaUV_2.y * edge_1.z - deltaUV_1.y * edge_2.z);
	tangent = glm::normalize(tangent);

	bitangent.x = f * (-deltaUV_2.x * edge_1.x + deltaUV_1.x * edge_2.x);
	bitangent.y = f * (-deltaUV_2.x * edge_1.y + deltaUV_1.x * edge_2.y);
	bitangent.z = f * (-deltaUV_2.x * edge_1.z + deltaUV_1.x * edge_2.z);
	bitangent = glm::normalize(bitangent);

	normal = glm::cross(tangent, bitangent);
}

