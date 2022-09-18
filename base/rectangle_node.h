#ifndef _RECTANGLE_NODE_H
#define _RECTANGLE_NODE_H
#include "node.h"

namespace gl
{
	class shader;
}
class rectangle_node : public node
{
public:
	rectangle_node(float width, float height, const glm::mat4& model_mat4);
	~rectangle_node();

protected:
	virtual bool initialize() override;
	virtual void drawing() override;

private:
	unsigned int build_vertices();
private:
	gl::shader* m_shader;
	unsigned int m_texture_id;

	float m_width;
	float m_height;
	glm::mat4 m_model_mat4;

	float* m_vertices;
};
#endif //_RECTANGLE_NODE_H
