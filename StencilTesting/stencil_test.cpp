#include "stencil_test.h"
#include "glad/glad.h"
#include "../base/geometry_node.h"
#include "../base/entity/cube.h"
stencil_test::stencil_test()
{
	entity::cube* p = new entity::cube(0.3f, "../resource/texture/container.jpg");
	add_child(p);
}

// void stencil_test::do_render_childs()
// {
//	glEnable(GL_STENCIL_TEST);
//	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//	glStencilFunc(GL_ALWAYS, 1, 0xFF); // ���е�Ƭ�ζ�Ӧ�ø���ģ�建��
//	glStencilMask(0xFF);
//	do_render_childs();
//
//
//	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//	glStencilMask(0x00);
//	do_render_childs();
//	glDisable(GL_STENCIL_TEST);
//}