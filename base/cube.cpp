#include "cube.h"
#include <glad/glad.h>
#include "../base/texture_loader.h"
#include "../base/system_env.h"
#include "../base/camera.h"

cube::cube(float width, const glm::mat4& model)
	: m_width(width)
	, m_model(model)
	, m_init(true)
	, m_shader(nullptr)
{

}

cube::~cube()
{

}

bool cube::initialize()
{
	//顶点数组对象
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	//顶点缓冲对象
	float* data = new float[5 * 4 * 6];
	int size = gen_buffer_data(data);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	delete[]data;

	//构建ebo
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_texture = gl::load_texture_2d("./texture/container.jpg");

	if (m_shader == nullptr)
	{
		m_shader = new gl::shader("./shader/cube/shader.vs", "./shader/cube/shader.fs");
		string error;
		m_shader->initialize(error);
		m_shader->use();
		m_shader->set_int("texture1", 0);
	}
	return true;
}

void cube::drawing()
{

	glBindVertexArray(m_vao);

	m_shader->use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glm::mat4 view(1.0f);
	view = system_env::instance()->get_camera()->get_view_matrix();
	m_shader->set_matrix4("view", view);

	glm::mat4 projection = get_projection_matrix4();
	m_shader->set_matrix4("projection", projection);

	m_shader->set_matrix4("model", m_model);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void cube::init()
{
	
}

int cube::gen_buffer_data(float* data)
{
	//(-width/2, width/2, -width/2)
	float px1 = -m_width / 2.0f;
	float py1 = m_width / 2.0f;
	float pz1 = -m_width / 2.0f;

	//(-widht/2, width/2, width/2)
	float px2 = -m_width / 2.0f;
	float py2 = m_width / 2.0f;
	float pz2 = m_width / 2.0f;
	
	//(width/2, width/2, width/2)
	float px3 = m_width / 2.0f;
	float py3 = m_width / 2.0f;
	float pz3 = m_width / 2.0f;


	//(width/2, width/2, -width/2)
	float px4 = m_width / 2.0f;
	float py4 = m_width / 2.0f;
	float pz4 = -m_width / 2.0f;

	//(-width/2, -width/2, -width/2)
	float px5 = -m_width / 2.0f;
	float py5 = -m_width / 2.0f;
	float pz5 = -m_width / 2.0f;

	//(-width/2, -width/2, width/2)
	float px6 = -m_width / 2.0f;
	float py6 = -m_width / 2.0f;
	float pz6 = m_width / 2.0f;

	//(width/2, -width/2, width/2)
	float px7 = m_width / 2.0f;
	float py7 = -m_width / 2.0f;
	float pz7 = m_width / 2.0f;

	//(width/2, -width/2, -width/2)
	float px8 = m_width / 2.0f;
	float py8 = -m_width / 2.0f;
	float pz8 = -m_width / 2.0f;

	float vertices[] = {
		px1, py1, pz1, 0.0f, 1.0f, 
		px2, py2, pz2, 0.0f, 0.0f,
		px3, py3, pz3, 1.0f, 0.0f,
		px4, py4, pz4, 1.0f, 1.0f, 

		px2, py2, pz2, 0.0f, 1.0f,
		px6, py6, pz6, 0.0f, 0.0f,
		px7, py7, pz7, 1.0f, 0.0f,
		px3, py3, pz3, 1.0f, 1.0f,

		px5, py5, pz5, 0.0f, 1.0,
		px6, py6, pz6, 0.0, 0.0,
		px7, py7, pz7, 0.0, 1.0,
		px8, py8, pz8, 1.0, 1.0,

		px1, py1, pz1, 1.0f, 1.0f,
		px5, py5, pz5, 0.0f, 1.0f,
		px8, py8, pz8, 0.0, 0.0,
		px4, py4, pz4, 0.0f, 1.0f,

		px1, py1, pz1, 0.0f, 1.0f,
		px5, py5, pz5, 0.0f, 0.0f,
		px6, py6, pz6, 0.0, 1.0,
		px2, py2, pz2, 1.0f, 1.0f,

		px4, py4, pz4, 1.0f, 1.0f,
		px3, py3, pz3, 0.0f, 1.0f,
		px7, py7, pz7, 0.0, 0.0,
		px8, py8, pz8, 1.0, 0.0,
	};
	memcpy(data, vertices, sizeof(vertices));
	return 5 * 4 * 6 * sizeof(float);
}

