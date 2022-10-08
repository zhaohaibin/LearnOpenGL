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

void node::do_render_childs()
{
	childs::iterator it = m_childs.begin();
	for (; it != m_childs.end(); ++it)
	{
		(*it)->render();
	}
}

void node::do_set_matrix()
{
	if (m_shader == nullptr)
		return;

	m_shader->use();
	if (m_model_matrix_need_update)
	{
		m_model_matrix_need_update = false;
		m_shader->set_matrix4("model", m_model_matrix);
	}
}

glm::mat4 node::get_ancestors_model()
{
	if (m_parent_node == nullptr)
		return glm::mat4(1.0f);
	return m_parent_node->get_ancestors_model()*m_parent_node->get_model_matrix();
}

