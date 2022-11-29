#include "../base/viewer.h"
#include "../base/node.h"
#include "animation_node.h"

int main()
{
	node* root = new node;
	root->add_child(new animation_node());
	viewer* _viewer = new viewer;
	_viewer->set_scene(root);
	_viewer->run();
	return 0;
}