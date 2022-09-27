#pragma once
#include "../base/node.h"


class coordinate_node_before_rendering_update_callback : public node_before_rendering_update_callback
{
protected:
	virtual void do_update(node* p);
};
class coordinate_systems_node : public node
{
public:
	coordinate_systems_node();
	~coordinate_systems_node();
};

