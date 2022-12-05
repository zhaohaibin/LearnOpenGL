#include "node.h"
#include "../base/system_env.h"
#include "../base/camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include "shader.h"


node::node(glm::mat4 model_matrix/* = glm::mat4(1.0f)*/)
	: m_init(true)
	, m_model_matrix_need_update(true)
	, m_model_matrix(model_matrix)
	, m_before_rendering_update_callback(nullptr)
	, m_id(0)
	, m_parent_node(nullptr)
	, m_curent_shader_index(0)
{

}

node::~node()
{

}

void node::add_child(node* p)
{
	m_childs.push_back(p);
	p->m_parent_node = this;
}

void node::remove_child(node* p)
{
	m_childs.remove(p);
}

void node::set_before_rendering_update_callback(node_before_rendering_update_callback* p)
{
	m_before_rendering_update_callback = p;
}

void node::set_id(unsigned int id)
{
	m_id = id;
}

unsigned int node::get_id()
{
	return m_id;
}

bool node::initialize()
{
	return true;
}

void node::drawing()
{

}

void node::render()
{
	do_render_childs();

	if (m_init)
	{
		m_init = false;
		initialize();
	}
	if (m_before_rendering_update_callback != nullptr)
		m_before_rendering_update_callback->do_update(this);

	do_set_matrix();
	drawing();
}

void node::set_model_matrix(glm::mat4 matrix)
{
	m_model_matrix = matrix;
	m_model_matrix_need_update = true;
}

glm::mat4 node::get_model_matrix()
{
	return m_model_matrix;
}

glm::mat4 node::get_merge_model_matrix()
{
	return get_ancestors_model()*m_model_matrix;
}

glm::mat4 node::get_projection_matrix4()
{
	view_port& vp = system_env::instance()->get_view_port();
	camera* _camera = system_env::instance()->get_camera();
	return glm::perspective(glm::radians(_camera->get_filed_view()), (float)vp.m_width / (float)vp.m_height, 0.1f, 100.f);
}

unsigned int node::create_shader(const shader_file& file)
{
	m_shader_files.push_back(file);
	return m_shader_files.size() - 1;
}

void node::switch_shader(unsigned char index)
{
	m_curent_shader_index = index;
}

void node::do_render_childs()
{
	childs::iterator it = m_childs.begin();
	for (; it != m_childs.end(); ++it)
	{
		(*it)->render();
	}
}

bool node::setup_shader()
{
	for (int i = 0; i < m_shader_files.size(); ++i)
	{
		gl::shader* p = new gl::shader(m_shader_files[i].m_vertex_shader_file, m_shader_files[i].m_frag_shader_file);
		string error;
		bool rt = p->initialize(error);
		if (rt == false) return false;
		m_shaders.push_back(p);
		p->use();
		update_uniform_value();
		setup_texture();
		
	}
	return true;
}

void node::update_uniform_value()
{

}

void node::setup_texture()
{

}

gl::shader* node::get_shader()
{
	return m_shaders[m_curent_shader_index];
}

void node::use_shader()
{
	if (m_shaders.size() <= m_curent_shader_index)
		return;
	m_shaders[m_curent_shader_index]->use();
}

void node::un_use_shader()
{
	if (m_shaders.size() <= m_curent_shader_index)
		return;
	m_shaders[m_curent_shader_index]->un_use();
}

void node::do_set_matrix()
{
	if (m_shaders.size() <= m_curent_shader_index)
		return;
	if (m_shaders[m_curent_shader_index] == nullptr)
		return;

	m_shaders[m_curent_shader_index]->use();
	if (m_model_matrix_need_update)
	{
		m_model_matrix_need_update = false;
		m_shaders[m_curent_shader_index]->set_matrix4("model", m_model_matrix);
	}
}

glm::mat4 node::get_ancestors_model()
{
	if (m_parent_node == nullptr)
		return glm::mat4(1.0f);
	return m_parent_node->get_ancestors_model()*m_parent_node->get_model_matrix();
}

