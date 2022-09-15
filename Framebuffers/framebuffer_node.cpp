#include "framebuffer_node.h"
#include <glad/glad.h>


framebuffer_node::framebuffer_node()
{
}


framebuffer_node::~framebuffer_node()
{
}

void framebuffer_node::render()
{
	m_framebuffer.use();
	do_render_childs();

	//°ó¶¨µ½Ä¬ÈÏÖ¡»º³å
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	drawing();
}

void framebuffer_node::drawing()
{

}

bool framebuffer_node::initialize()
{
	
	return true;
}
