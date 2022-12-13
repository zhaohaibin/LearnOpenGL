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
, m_vertex_texture_coord_data(nullptr)
, m_is_draw_arrays(true)
, m_element_data(nullptr)
, m_element_count(0)
, m_primitive(GL_TRIANGLES)
{
}

bool geometry_node::initialize()
{
	if (setup_shader() == false)
		return false;

	//�����������
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	bool rt = setup_vertex_array();
	if (rt == false)
		return false;

	rt = setup_vertex_color_array();
	rt = setup_vertex_normal_array();
	rt = setup_vertex_texture_array();
	rt = setup_element();

	setup_layout_data();
	glBindVertexArray(0);

	return true;
}

void geometry_node::drawing()
{
	do_use_shader();
	active_texture();
	glBindVertexArray(m_vao);
	m_state_set.do_set_state();
	if (m_vertex_need_update)
	{
		m_vertex_need_update = false;
		update_vertex_array();
	}
	//glEnable(GL_PROGRAM_POINT_SIZE);
	if (m_is_draw_arrays)
		glDrawArrays(m_primitive, 0, m_vertex_data_length / (sizeof(float) * 3));
	else
		glDrawElements(m_primitive, m_element_count, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	un_use_shader();
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

void geometry_node::set_vertex_texture(float* data, unsigned int length, unsigned int layout_index, unsigned int step/* = 2*/)
{
	m_vertex_texture_coord_data = data;
	m_vertex_texture_coord_data_lenght = length;
	m_vertex_texture_coord_layout_index = layout_index;
	m_vertex_texture_coord_step = step;
}

void geometry_node::set_layout_data(float* data, unsigned int length, unsigned int layout_index, unsigned int step /*= 2*/)
{
	m_layout_datas.push_back(layout_data(data, length, layout_index, step));
}

void geometry_node::set_elements(unsigned int* data, unsigned int length)
{
	m_element_data = data;
	m_element_count = length;
}

void geometry_node::set_draw_array(bool is_draw_array)
{
	m_is_draw_arrays = is_draw_array;
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

void geometry_node::add_material(const material& _material)
{
	m_materials.push_back(_material);
}

node_state* geometry_node::get_state_set()
{
	return &m_state_set;
}

bool geometry_node::setup_layout_data()
{
	for (int i = 0; i < m_layout_datas.size(); ++i)
	{
		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, m_layout_datas[i].m_length, m_layout_datas[i].m_data, GL_STATIC_DRAW);
		glVertexAttribPointer(m_layout_datas[i].m_index, m_layout_datas[i].m_step, 
			GL_FLOAT, GL_FALSE, m_layout_datas[i].m_step * sizeof(float), (void*)0);
		glEnableVertexAttribArray(m_layout_datas[i].m_index);
	}
	return true;
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
	glVertexAttribPointer(m_vertex_texture_coord_layout_index,
		m_vertex_texture_coord_step, GL_FLOAT, GL_FALSE, 
		m_vertex_texture_coord_step * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_vertex_texture_coord_layout_index);
	return true;
}

bool geometry_node::setup_element()
{
	if (m_element_data != nullptr)
	{
		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_element_count, m_element_data, GL_STATIC_DRAW);
	}
	return true;
}

void geometry_node::update_uniform_value()
{
	gl::shader* m_shader = get_shader();
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
	gl::shader* m_shader = get_shader();
	for (int i = 0; i < m_materials.size(); ++i)
	{
		if(m_materials[i].m_id == -1)
			m_materials[i].m_id = gl::load_texture_2d(m_materials[i].m_file);
		m_shader->set_int(m_materials[i].m_name, i);
	}
}

void geometry_node::do_use_shader()
{
	use_shader();
	update_uniform_value();
	update_mvp();
	//��������
}

void geometry_node::update_mvp()
{
	glm::mat4 view(1.0f);
	view = system_env::instance()->get_camera()->get_view_matrix();
	gl::shader* p = get_shader();
	p->set_matrix4("view", view);

	glm::mat4 projection = get_projection_matrix4();
	p->set_matrix4("projection", projection);

	p->set_matrix4("model", /*m_model_matrix*/get_merge_model_matrix());
}

void geometry_node::active_texture()
{
	for (int i = 0; i < m_materials.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_materials[i].m_id);
	}
}
