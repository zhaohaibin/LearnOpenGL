#include "line_node.h"
#include <glad/glad.h>
#include "shader.h"
#include "system_env.h"
#include "camera.h"

line_node::line_node(const std::vector<point>& points)
	: m_points(points)
{
}

bool line_node::initialize()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_points.size() * sizeof(point), &m_points[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	if (m_shader == nullptr)
	{
		const string path = "D:/Workspace/opengl/WorkSpace/LearnOpenGL/base/";
		m_shader = new gl::shader(path + "/shader/line_node/shader.vs", path + "/shader/line_node/shader.fs");
		string error;
		return m_shader->initialize(error);
	}
	return true;
}

void line_node::drawing()
{
	m_shader->use();
	glm::mat4 view(1.0f);
	view = system_env::instance()->get_camera()->get_view_matrix();
	m_shader->set_matrix4("view", view);

	glm::mat4 projection = get_projection_matrix4();
	m_shader->set_matrix4("projection", projection);

	m_shader->set_matrix4("model", get_merge_model_matrix());

	glBindVertexArray(m_vao);
	glDrawArrays(GL_LINES, 0, m_points.size());
	glBindVertexArray(0);
	m_shader->un_use();
}

