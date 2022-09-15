#include "node.h"
#include "../base/system_env.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

node::node()
	: m_init(true)
{

}

node::~node()
{

}

void node::add_child(node* p)
{
	m_childs.push_back(p);
}

void node::remove_child(node* p)
{
	m_childs.remove(p);
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

	drawing();
}

glm::mat4 node::get_projection_matrix4()
{
	view_port& vp = system_env::instance()->get_view_port();
	return glm::perspective(glm::radians(45.0f), (float)vp.m_width / (float)vp.m_height, 0.1f, 100.f);
}

void node::do_render_childs()
{
	childs::iterator it = m_childs.begin();
	for (; it != m_childs.end(); ++it)
	{
		(*it)->render();
	}
}

