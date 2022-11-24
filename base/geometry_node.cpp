#include "geometry_node.h"
#include "shader.h"
#include <glad/glad.h>
#include "system_env.h"
#include "camera.h"
#include "texture_loader.h"

geometry_node::geometry_node(glm::mat4 model_matrix /*= glm::mat4(1.0f)*/) : node(model_matrix)
, m_vertex_data(nullptr)
, m_vertex_data_length(0)
, m_vertex_color_data(nullptr)
, m_vertex_color_data_length(0)
, m_vertex_normal_data(nullptr)
, m_vertex_normal_data_length(0)
, m_vertex_need_update(false)
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
	rt = setup_vertex_texture_array();
	glBindVertexArray(0);

	return true;
}

void geometry_node::drawing()
{
	use_shader();
	active_texture();
	glBindVertexArray(m_vao);
	m_state_set.do_set_state();
	if (m_vertex_need_update)
	{
		m_vertex_need_update = false;
		update_vertex_array();
	}
	//glEnable(GL_PROGRAM_POINT_SIZE);
	glDrawArrays(m_primitive, 0, m_vertex_data_length / (sizeof(float) * 3));
	glBindVertexArray(0);
	m_shader->un_use();
}

void geometry_node::set_primitive(unsigned int primitive)
{
	m_primitive = primitive;
}

void geometry_node::set_vertex(float* data, unsigned int length, unsigned int layout_index)
{
	m_vertex_data = data;
	m_vertex_data_length = length;
	m_vertex_layout_index = layout_index;
}

void geometry_node::update_vertex(float* data, unsigned int length)
{
	m_vertex_data = data;
	m_vertex_data_length = length;
	m_vertex_need_update = true;
}

void geometry_node::set_vertex_color(float* data, unsigned int length, unsigned int layout_index)
{
	m_vertex_color_data = data;
	m_vertex_color_data_length = length;
	m_vertex_color_layout_index = layout_index;
}

void geometry_node::set_vertex_normal(float* data, unsigned int length, unsigned int layout_index)
{
	m_vertex_normal_data = data;
	m_vertex_normal_data_length = length;
	m_vertex_normal_layout_index = layout_index;
}

void geometry_node::set_vertex_texture(float* data, unsigned int length, unsigned int layout_index)
{
	m_vertex_texture_coord_data = data;
	m_vertex_texture_coord_data_lenght = length;
	m_vertex_texture_coord_layout_index = layout_index;
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

void geometry_node::add_material(const std::string& name, const std::string file)
{
	material _material;
	_material.m_id = -1;
	_material.m_name = name;
	_material.m_file = file;

	m_materials.push_back(_material);
}

node_state* geometry_node::get_state_set()
{
	return &m_state_set;
}

bool geometry_node::setup_vertex_array()
{
	if (m_vertex_data == nullptr)
		return false;

	glGenBuffers(1, &m_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_data_length, m_vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(m_vertex_layout_index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_vertex_layout_index);
	return true;
}

bool geometry_node::update_vertex_array()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_data_length, m_vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(m_vertex_layout_index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_vertex_layout_index);
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
	glVertexAttribPointer(m_vertex_color_layout_index, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_vertex_color_layout_index);
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
	glVertexAttribPointer(m_vertex_normal_layout_index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_vertex_normal_layout_index);
	return true;
}

bool geometry_node::setup_vertex_texture_array()
{
	if (m_vertex_texture_coord_data == nullptr)
		return false;

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_texture_coord_data_lenght, m_vertex_texture_coord_data, GL_STATIC_DRAW);
	glVertexAttribPointer(m_vertex_texture_coord_layout_index, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_vertex_texture_coord_layout_index);
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
	setup_texture();
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

void geometry_node::setup_texture()
{
	for (int i = 0; i < m_materials.size(); ++i)
	{
		m_materials[i].m_id = gl::load_texture_2d(m_materials[i].m_file);
		m_shader->set_int(m_materials[i].m_name, i);
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

void geometry_node::active_texture()
{
	for (int i = 0; i < m_materials.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_materials[i].m_id);
	}
}
