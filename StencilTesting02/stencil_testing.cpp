#include "stencil_testing.h"
#include "..\base\geometry_node.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include "../base/entity/cube.h"

stencil_testing::stencil_testing()
{
	m_cube = new cube();
	add_child(m_cube);

	glm::mat4 model(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.5f));
	m_entity_cube = new entity::cube(0.5, "./shader/brickwall.jpg", model);
	add_child(m_entity_cube);

	float vertex[18] =
	{
		-0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,

		-0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5
	};

	float texture_coord[12] =
	{
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,

		0.0, 0.0,
		1.0, 1.0,
		1.0, 0.0
	};
	m_rect = m_cube->create_face(vertex, sizeof(vertex), texture_coord, sizeof(texture_coord), "./shader/powerup_increase.png");
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-2.0, 0.0, -0.5));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0, 0.0, 0.5));
	m_rect->set_model_matrix(model);
	add_child(m_rect);
}

void stencil_testing::do_render_childs()
{
	//glEnable(GL_DEPTH_TEST);
	m_cube->render();
	glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	m_entity_cube->render();

	glStencilFunc(GL_EQUAL, 2, 0xFF);

	m_rect->render();
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
}

cube::cube()
{
	//face 1
	float vertex[18] = 
	{
		-0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,

		-0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5
	};

	float texture_coord[12] = 
	{
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,

		0.0, 0.0,
		1.0, 1.0,
		1.0, 0.0
	};
	m_face_1 = create_face(vertex, sizeof(vertex), texture_coord, sizeof(texture_coord));
	
	add_child(m_face_1);
}

void cube::do_render_childs()
{
	//启用模板测试
	glEnable(GL_STENCIL_TEST);

	//设置填充策略
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//设置模板比较方式，参考值和掩码
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	glStencilMask(0xFF);
	glm::mat4 model(1.0);
	m_face_1->set_model_matrix(model);
	m_face_1->render();

	//面2
	glStencilFunc(GL_ALWAYS, 2, 0xFF);
	model = glm::translate(model, glm::vec3(0.5f, 0.0f, -1.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	m_face_1->set_model_matrix(model);
	m_face_1->render();

	//面3
	glStencilFunc(GL_ALWAYS, 3, 0xFF);
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	m_face_1->set_model_matrix(model);
	m_face_1->render();

	//面4
	glStencilFunc(GL_ALWAYS, 4, 0xFF);
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-0.5f, 0.0f, -1.0f));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	m_face_1->set_model_matrix(model);
	m_face_1->render();
}

geometry_node* cube::create_face(float* vertex, unsigned int vertex_length,
	float* texture_coord, unsigned int texture_coord_length)
{
	float * vertex_data = new float[vertex_length / sizeof(float)];
	memcpy(vertex_data, vertex, vertex_length);
	float* texture_coord_data = new float[texture_coord_length / sizeof(float)];
	memcpy(texture_coord_data, texture_coord, texture_coord_length);
	geometry_node* p = new geometry_node;
	shader_file _file;
	_file.m_vertex_shader_file = "./shader/cube/shader.vs";
	_file.m_frag_shader_file = "./shader/cube/shader.fs";
	p->create_shader(_file);
	
	p->set_vertex(vertex_data, vertex_length, 0);
	p->set_vertex_texture(texture_coord_data, texture_coord_length, 1);
	p->add_material("texture_1", "./shader/cube/back.jpg");

	return p;
}

geometry_node* cube::create_face(float* vertex, unsigned int vertex_length, 
	float* texture_coord, unsigned int texture_coord_length, 
	const std::string& texture_file)
{
	float * vertex_data = new float[vertex_length / sizeof(float)];
	memcpy(vertex_data, vertex, vertex_length);
	float* texture_coord_data = new float[texture_coord_length / sizeof(float)];
	memcpy(texture_coord_data, texture_coord, texture_coord_length);
	geometry_node* p = new geometry_node;
	shader_file _file;
	_file.m_vertex_shader_file = "./shader/cube/shader.vs";
	_file.m_frag_shader_file = "./shader/cube/shader.fs";
	p->create_shader(_file);

	p->set_vertex(vertex_data, vertex_length, 0);
	p->set_vertex_texture(texture_coord_data, texture_coord_length, 1);
	p->add_material("texture_1", texture_file);

	return p;
}
