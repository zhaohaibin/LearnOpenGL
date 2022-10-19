#include "geometry_node.h"
#include "shader.h"
#include <glad/glad.h>
#include "system_env.h"
#include "camera.h"

geometry_node::geometry_node(glm::mat4 model_matrix /*= glm::mat4(1.0f)*/) : node(model_matrix)
, m_vertex_data(nullptr)
, m_vertex_data_length(0)
, m_vertex_color_data(nullptr)
, m_vertex_color_data_length(0)
, m_vertex_normal_data(nullptr)
, m_vertex_normal_data_length(0)
{
}

bool geometry_node::initialize()
{
	if (setup_shader() == false)
		return false;

	//顶点数组对象
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	bool rt = setup_vertex_array();
	if (rt == false)
		return false;

	rt = setup_vertex_color_array();
	rt = setup_vertex_normal_array();
	glBindVertexArray(0);
	return true;
}

void geometry_node::drawing()
{
	use_shader();
	glBindVertexArray(m_vao);
	glDrawArrays(m_primitive, 0, m_vertex_data_length / (sizeof(float) * 3));
	glBindVertexArray(0);
	m_shader->un_use();
}

void geometry_node::set_primitive(unsigned int primitive)
{
	m_primitive = primitive;
}

void geometry_node::set_vertex(float* data, unsigned int length)
{
	m_vertex_data = data;
	m_vertex_data_length = length;
}

void geometry_node::set_vertex_color(float* data, unsigned int length)
{
	m_vertex_color_data = data;
	m_vertex_color_data_length = length;
}

void geometry_node::set_vertex_normal(float* data, unsigned int length)
{
	m_vertex_normal_data = data;
	m_vertex_normal_data_length = length;
}

void geometry_node::set_shader_file(const std::string& vertex_shader_file, const std::string& frag_shader_file)
{
	m_vertex_shader_file = vertex_shader_file;
	m_frag_shader_file = frag_shader_file;
}

void geometry_node::set_shader_value(const std::string& name, unsigned int value)
{
	if (m_shader_uniform_value.m_uint_value.find(name) != m_shader_uniform_value.m_uint_value.end())
	{
		m_shader_uniform_value.m_uint_value[name] = value;
	}
	else
	{
		m_shader_uniform_value.m_uint_value.insert(std::make_pair(name, value));
	}
}

void geometry_node::set_shader_value(const std::string& name, float value)
{
	if (m_shader_uniform_value.m_float_value.find(name) != m_shader_uniform_value.m_float_value.end())
	{
		m_shader_uniform_value.m_float_value[name] = value;
	}
	else
	{
		m_shader_uniform_value.m_float_value.insert(std::make_pair(name, value));
	}
}

void geometry_node::set_shader_value(const std::string& name, const glm::vec3& value)
{
	if (m_shader_uniform_value.m_vec3_float_value.find(name) != m_shader_uniform_value.m_vec3_float_value.end())
	{
		m_shader_uniform_value.m_vec3_float_value[name] = value;
	}
	else
	{
		m_shader_uniform_value.m_vec3_float_value.insert(std::make_pair(name, value));
	}
}

void geometry_node::set_shader_value(const std::string& name, const glm::vec4& value)
{
	if (m_shader_uniform_value.m_vec4_float_value.find(name) != m_shader_uniform_value.m_vec4_float_value.end())
	{
		m_shader_uniform_value.m_vec4_float_value[name] = value;
	}
	else
	{
		m_shader_uniform_value.m_vec4_float_value.insert(std::make_pair(name, value));
	}
}

bool geometry_node::setup_vertex_array()
{
	if (m_vertex_data == nullptr)
		return false;

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_data_length, m_vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	return true;
}

bool geometry_node::setup_vertex_color_array()
{
	if (m_vertex_color_data == nullptr)
		return false;

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_color_data_length, m_vertex_color_data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	return true;
}

bool geometry_node::setup_vertex_normal_array()
{
	if (m_vertex_normal_data == nullptr)
		return false;

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_normal_data_length, m_vertex_normal_data, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	return true;
}

bool geometry_node::setup_shader()
{
	m_shader = new gl::shader(m_vertex_shader_file, m_frag_shader_file);
	string error;
	bool rt = m_shader->initialize(error);
	if (rt == false) return false;

	m_shader->use();
	update_uniform_value();
	m_shader->un_use();
	return rt;
}

void geometry_node::update_uniform_value()
{
	std::map<string, unsigned int>::iterator uint_value_it = m_shader_uniform_value.m_uint_value.begin();
	for (; uint_value_it != m_shader_uniform_value.m_uint_value.end(); ++uint_value_it)
	{
		m_shader->set_int(uint_value_it->first, uint_value_it->second);
	}

	std::map<string, float>::iterator float_value_it = m_shader_uniform_value.m_float_value.begin();
	for (; float_value_it != m_shader_uniform_value.m_float_value.end(); ++float_value_it)
	{
		m_shader->set_float(float_value_it->first, float_value_it->second);
	}

	std::map<std::string, glm::vec3>::iterator vec3_float_value_it = m_shader_uniform_value.m_vec3_float_value.begin();
	for (; vec3_float_value_it != m_shader_uniform_value.m_vec3_float_value.end(); ++vec3_float_value_it)
	{
		m_shader->set_vec3f(vec3_float_value_it->first, vec3_float_value_it->second);
	}
}

void geometry_node::use_shader()
{
	m_shader->use();
	update_uniform_value();
	update_mvp();
	//激活纹理
}

void geometry_node::update_mvp()
{
	glm::mat4 view(1.0f);
	view = system_env::instance()->get_camera()->get_view_matrix();
	m_shader->set_matrix4("view", view);

	glm::mat4 projection = get_projection_matrix4();
	m_shader->set_matrix4("projection", projection);

	m_shader->set_matrix4("model", /*m_model_matrix*/get_merge_model_matrix());
}
