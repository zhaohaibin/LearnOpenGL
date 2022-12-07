#ifndef _STENCIL_TEST_H
#define _STENCIL_TEST_H
#include "../base/node.h"

class geometry_node;
namespace entity
{
	class cube;
}
class stencil_test : public node
{
public:
	stencil_test();

protected:
	void do_render_childs();
private:
	geometry_node* m_geo_node_1;
	entity::cube* m_cube;
};
#endif //_STENCIL_TEST_H
