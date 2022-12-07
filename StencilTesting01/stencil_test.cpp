#include "stencil_test.h"
#include "..\base\geometry_node.h"
#include "..\base\entity\cube.h"
#include "glad\glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float* vertex_data_1 = nullptr;
float* texture_coord = nullptr;

stencil_test::stencil_test()
	: node()
{
	float rect_tangle[18] = {
		-0.5, 0.5, 0.5,
		-0.5, -0.5, 0.5,
		0.5, -0.5, 0.5,

		-0.5, 0.5, 0.5,
		0.5, -0.5, 0.5,
		0.5, 0.5, 0.5
	};

	float temp[12] = {
		0.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		0.0, 1.0,
		1.0, 0.0,
		1.0, 1.0
	};
	vertex_data_1 = new float[sizeof(rect_tangle)];
	memcpy(vertex_data_1, rect_tangle, sizeof(rect_tangle));
	m_geo_node_1 = new geometry_node;

	m_geo_node_1->set_vertex(vertex_data_1, sizeof(rect_tangle), 0);

	texture_coord = new float[sizeof(temp)];
	memcpy(texture_coord, temp, sizeof(temp));
	m_geo_node_1->set_vertex_texture(texture_coord, sizeof(temp), 1);
	m_geo_node_1->add_material("texture_1", "./shader/brickwall.jpg");
	shader_file _file;
	_file.m_vertex_shader_file = "./shader/rect.vs";
	_file.m_frag_shader_file = "./shader/rect.fs";
	m_geo_node_1->create_shader(_file);

	add_child(m_geo_node_1);

	glm::mat4 model(1.0);
	glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	m_cube = new entity::cube(0.8, "./shader/awesomeface.png");
	add_child(m_cube);
}

void stencil_test::do_render_childs()
{
	//启用模板测试
	glEnable(GL_STENCIL_TEST);

	//设置填充策略
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//设置模板比较方式，参考值和掩码
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	glStencilMask(0xFF);
	m_geo_node_1->render();
	
	glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	
	m_cube->render();
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
}

