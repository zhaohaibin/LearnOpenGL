#include "../base/viewer.h"
#include "stencil_testing.h"

void main()
{
	viewer* _viewer = new viewer;
	_viewer->set_scene(new stencil_testing());
	_viewer->run();
	return;
}