#include "../base/viewer.h"
#include "../base/node.h"
#include "stencil_test.h"

int main()
{
	node* root = new node;
	root->add_child(new stencil_test());
	viewer* _viewer = new viewer;
	_viewer->set_scene(root);
	_viewer->run();
	return 0;
}