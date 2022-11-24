#include "vegetation_node.h"
#include "../base/geometry_node.h"

#include <vector>
#include "glad/glad.h"
using namespace std;

float vertex_data[] = {
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f};
float texture_coord[] = {
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f };

vegetation_node::vegetation_node()
{
	geometry_node* vegetation = new geometry_node;
	vegetation->set_vertex(vertex_data, sizeof(vertex_data), 0);
	vegetation->set_vertex_texture(texture_coord, sizeof(texture_coord), 1);
	vegetation->set_vertex_shader_file("./shader/vegetation.vs");
	vegetation->set_frag_shader_file("./shader/vegetation.fs");
	vegetation->add_material("texture_1", "./resources/grass.png");
	vegetation->set_primitive(GL_TRIANGLES);
	add_child(vegetation);
}

vegetation_node::~vegetation_node()
{
}
