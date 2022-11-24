#include "node_state.h"
#include <glad/glad.h>

node_state::node_state()
	: m_enable_blend(false)
{

}

node_state::~node_state()
{

}

void node_state::enable_blend()
{
	m_enable_blend = true;
}

void node_state::disable_blend()
{
	m_enable_blend = false;
}

void node_state::set_blend_func(int sfactor, int dfactor)
{
	m_blend_fun.clear();
	m_blend_fun.push_back(sfactor);
	m_blend_fun.push_back(dfactor);
}

void node_state::set_blend_func(unsigned int sfactorRGB, unsigned int dfactorRGB, unsigned int sfactorAlpha, unsigned int dfactorAlpha)
{
	m_blend_fun.clear();
	m_blend_fun.push_back(sfactorRGB);
	m_blend_fun.push_back(dfactorRGB);
	m_blend_fun.push_back(sfactorAlpha);
	m_blend_fun.push_back(dfactorAlpha);
}

void node_state::do_set_state()
{
	do_set_blend();
}

void node_state::do_set_blend()
{
	if (m_enable_blend == false)
		return;

	glEnable(GL_BLEND);

	if (m_blend_fun.size() == 2)
	{
		glBlendFunc(m_blend_fun[0], m_blend_fun[1]);
	}
	else if (m_blend_fun.size() == 4)
	{
		glBlendFuncSeparate(m_blend_fun[0], m_blend_fun[1], m_blend_fun[2], m_blend_fun[3]);
	}
}

