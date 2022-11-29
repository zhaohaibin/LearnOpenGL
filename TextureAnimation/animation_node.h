#ifndef _ANIMATION_NODE_H
#define _ANIMATION_NODE_H
#include "../base/node.h"

class animation_before_rendering_update_callback : public node_before_rendering_update_callback
{
protected:
	virtual void do_update(node* p);
};
class animation_node : public node
{
public:
	animation_node();

private:
	animation_before_rendering_update_callback* m_callback;
};
#endif //_ANIMATION_NODE_H
