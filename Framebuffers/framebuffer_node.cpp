#include "framebuffer_node.h"
#include <glad/glad.h>
#include "../base/shader.h"
#include "../base/texture_loader.h"


framebuffer_node::framebuffer_node()
	: m_shader(nullptr)
{
}


framebuffer_node::~framebuffer_node()
{
}

void framebuffer_node::render()
{
	if (m_init)
	{
		m_init = false;
		initialize();
	}

	m_framebuffer.use();
	do_render_childs();

	//°ó¶¨µ½Ä¬ÈÏÖ¡»º³å
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	drawing();
}

void framebuffer_node::drawing()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
	m_shader->use();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	m_shader->un_use();
}

bool framebuffer_node::initialize()
{
	string path = "D:/Workspace/opengl/WorkSpace/LearnOpenGL/Framebuffers/";
	m_shader = new gl::shader(path+"/shader/framebuffer_node/shader.vs", path+"/shader/framebuffer_node/shader.fs");
	string error;
	if (m_shader->initialize(error) == false)
		return false;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	float vertex[] = {
		-1.0f, 1.0f, 0.0, 1.0, //×óÉÏ½Ç
		-1.0f, -1.0f, 0.0, 0.0, //×óÏÂ½Ç
		1.0f, 1.0f, 1.0, 1.0, //ÓÒÉÏ½Ç
		1.0f, 1.0f, 1.0, 1.0, //ÓÒÉÏ½Ç
		-1.0f, -1.0f, 0.0, 0.0, //×óÏÂ½Ç
		1.0f, -1.0f, 1.0, 0.0 //ÓÒÏÂ½Ç
	};

// 	float vertex[] = {
// 		-0.5f, 0.5f, 0.0, 0.5, //×óÉÏ½Ç
// 		-0.5f, -0.5f, 0.0, 0.0, //×óÏÂ½Ç
// 		0.5f, 0.5f, 0.5, 0.5, //ÓÒÉÏ½Ç
// 		0.5f, 0.5f, 0.5, 0.5, //ÓÒÉÏ½Ç
// 		-0.5f, -0.5f, 0.0, 0.0, //×óÏÂ½Ç
// 		0.5f, -0.5f, 0.5, 0.0 //ÓÒÏÂ½Ç
// 	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//m_texture_id = gl::load_texture_2d("./texture/container.jpg");
	m_texture_id = m_framebuffer.get_texture();
	m_shader->use();
	m_shader->set_int("texture_1", 0);
	m_shader->un_use();
	return true;
}
