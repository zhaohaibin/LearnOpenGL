#ifndef _POINT_SPRITE_H
#define _POINT_SPRITE_H
#include "geometry_node.h"

/*
	控制点的显示
	void glPointParameteri(GLenum pname, GLint param);
	void glPointParameterf(GLenum pname, GLfloat param);
	void glPointParameteriv(GLenum pname, const GLint* param);
	void glPointParameteriv(GLenum pname, const GLfloat* param);

	pname 必须是GL_POINT_SPRITE_COORD_ORIGIN、GL_POINT_FADE_THRESHOLD_SIZE.
		GL_POINT_SPRITE_COORD_ORIGIN对应的param 必须是GL_LOWER_LEFT或者GL_UPPER_LEFT
		GL_POINT_FADE_THRESHOLD_SIZE对应的param 必须是
*/
class point_sprite : public geometry_node
{
public:
	point_sprite(float size, glm::mat4 model_matrix = glm::mat4(1.0f));

protected:
	virtual bool initialize() override;
	virtual void drawing() override;
private:
	float m_size;
};
#endif //_POINT_SPRITE_H
