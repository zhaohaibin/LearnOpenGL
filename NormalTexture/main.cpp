#include "../base/viewer.h"
#include "normal_texture_node.h"

void main()
{
	viewer* _viewer = new viewer;
	node* root = new node;
	//root->add_child(new normal_texture_node);
	_viewer->set_scene(new normal_texture_node);
	_viewer->run();
	return;
}