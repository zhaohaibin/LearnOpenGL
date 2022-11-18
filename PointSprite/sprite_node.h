#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

#include "../base/node.h"

class sprite_node_update_callback : public node_before_rendering_update_callback
{
protected:
	virtual void do_update(node* p);
};

class sprite_node : public node
{
public:
	sprite_node();
};
#endif //SPRITE_NODE_H
