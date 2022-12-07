#include "stencil_test.h"
#include "glad/glad.h"
#include "../base/geometry_node.h"
#include "../base/entity/cube.h"
#include "glm/ext/matrix_transform.inl"
stencil_test::stencil_test()
{
	m_cube = new entity::cube(0.3f, "../resource/texture/container.jpg");

	shader_file _file;
	const string path = "D:/Workspace/opengl/WorkSpace/LearnOpenGL/base/";
	_file.m_vertex_shader_file = path + "/shader/cube/shader.vs";
	_file.m_frag_shader_file = path + "/shader/cube/shader_2.fs";
	m_cube->create_shader(_file);
	add_child(m_cube);
}

 void stencil_test::do_render_childs()
 {
	m_cube->switch_shader(0);
	glm::mat4 model = glm::mat4(1.0);
	m_cube->set_model_matrix(model);
	//启用模板测试
	glEnable(GL_STENCIL_TEST);

	//设置填充策略
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//设置模板比较方式，参考值和掩码
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	glStencilMask(0xFF);
	node::do_render_childs();

	float scale = 1.1;
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	m_cube->set_model_matrix(model);
	m_cube->switch_shader(1);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	//glStencilMask(0x00);
	node::do_render_childs();

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glDisable(GL_STENCIL_TEST);
}