#ifndef _STENCIL_TESTING_H
#define _STENCIL_TESTING_H
#include "../base/node.h"

class geometry_node;
class cube;
namespace entity
{
	class cube;
}
class stencil_testing : public node
{
public:
	stencil_testing();

protected:
	virtual void do_render_childs() override;
private:
	cube* m_cube;

	entity::cube* m_entity_cube;

	geometry_node* m_rect;
};

class cube : public node
{
public:
	cube();

protected:
	virtual void do_render_childs() override;

public:
	geometry_node* create_face(float* vertex, unsigned int vertex_length,
		float* texture_coord, unsigned int texture_coord_length);
	geometry_node* create_face(float* vertex, unsigned int vertex_length,
		float* texture_coord, unsigned int texture_coord_length, const std::string& texture_file);
private:
	geometry_node* m_face_1;
};
#endif //_STENCIL_TESTING_H
