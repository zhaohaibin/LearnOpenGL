#include "rectangle_node.h"
#include <glad/glad.h>
#include "../base/shader.h"
#include "../base/camera.h"
#include "system_env.h"
#include "../base/texture_loader.h"

rectangle_node::rectangle_node()
{

}

rectangle_node::~rectangle_node()
{

}

bool rectangle_node::initialize()
{
	string path = "D:/Workspace/opengl/WorkSpace/LearnOpenGL/base/shader/";
	string error;
	m_shader = new gl::shader(path + "trianglenode.vs", path + "triangle_node.fs");
	bool rt = m_shader->initialize(error);
	if (rt == false)
		return rt;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	float vertices[] = { 0.5f, 0.5f, 0.0f,//ÓÒÉÏ½Ç
		0.5f, -0.5f, 0.0f,//ÓÒÏÂ½Ç
		-0.5f, -0.5f, 0.0f,//×óÏÂ½Ç
		-0.5f, 0.5f, 0.0f //×óÉÏ½Ç
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	float color[] = { 1.0f, 1.0f,//ÓÒÉÏ½Ç
		1.0, 0.0,//ÓÒÏÂ½Ç
		0.0, 0.0,//×óÏÂ½Ç
		0.0, 1.0 //×óÉÏ½Ç
	};
	unsigned int vbo1;
	glGenBuffers(1, &vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	m_shader->use();
	m_texture_id = gl::load_texture_2d("./texture/container.jpg");
	m_shader->set_int("texture_1", 0);
	m_shader->un_use();
	return true;
}

void rectangle_node::drawing()
{
	m_shader->use();

	glm::mat4 view(1.0f);
	view = system_env::instance()->get_camera()->get_view_matrix();
	m_shader->set_matrix4("view", view);

	glm::mat4 projection = get_projection_matrix4();
	m_shader->set_matrix4("projection", projection);

	//m_shader->set_matrix4("model", m_model);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

