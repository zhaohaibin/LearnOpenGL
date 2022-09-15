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
	rectangle_node();
	~rectangle_node();

protected:
	virtual bool initialize() override;
	virtual void drawing() override;

private:
	gl::shader* m_shader;
};
#endif //_RECTANGLE_NODE_H
