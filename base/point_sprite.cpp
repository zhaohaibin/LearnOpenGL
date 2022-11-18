#include "point_sprite.h"
#include "glad/glad.h"

point_sprite::point_sprite(float size, glm::mat4 model_matrix /*= glm::mat4(1.0f)*/)
	: geometry_node(model_matrix)
	, m_size(size)
{
	
}

bool point_sprite::initialize()
{
	bool rt = geometry_node::initialize();
	if (rt == true)
		set_primitive(GL_POINTS);
	return rt;
}

void point_sprite::drawing()
{	
	//设置点精灵中 贴图的原点 位置为 左上角
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);

	glEnable(GL_PROGRAM_POINT_SIZE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	geometry_node::drawing();

	glDisable(GL_BLEND);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

