#include "basic_lighting_node.h"
#include "../base/cube.h"

#include "../base/geometry_node.h"
#include "../base/system_env.h"
#include "../base/camera.h"


class geometry_node_before_rendering_update_callback : public node_before_rendering_update_callback
{
public:
	geometry_node_before_rendering_update_callback() {}
	~geometry_node_before_rendering_update_callback() {}
protected:
	virtual void do_update(node* p)
	{
		glm::vec3 pos = system_env::instance()->get_camera()->get_position();
		geometry_node* geo_node = dynamic_cast<geometry_node*>(p);
		if (geo_node != nullptr)
		{
			geo_node->set_shader_value("view_pos", pos);
		}
	}
};
basic_lighting_node::basic_lighting_node()
{
	geometry_node* geo_node = new geometry_node;
	geo_node->set_before_rendering_update_callback(new geometry_node_before_rendering_update_callback());
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
	};
	float* vertex_data = new float[3 * 6 * 6];
	memcpy(vertex_data, vertices, 3 * 6 * 6 * sizeof(float));
	geo_node->set_vertex(vertex_data, 3 * 6 * 6 * sizeof(float), 0);

	float vertices_normal[] = {
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	float* vertex_normal_data = new float[3 * 6 * 6];
	memcpy(vertex_normal_data, vertices_normal, 3 * 6 * 6 * sizeof(float));
	geo_node->set_vertex_normal(vertex_normal_data, 3 * 6 * 6 * sizeof(float), 2);

	float vertices_color[] = {
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,

		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,

		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,

		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,

		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,

		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
		0.93f,0.42f, 0.18,1.0f,
	};
	float* vertex_color_data = new float[4 * 6 * 6];
	memcpy(vertex_color_data, vertices_color, 4 * 6 * 6 * sizeof(float));
	geo_node->set_vertex_color(vertex_color_data, 4 * 6 * 6 * sizeof(float), 1);
	geo_node->set_primitive(GL_TRIANGLES);
	geo_node->set_shader_file("./shader/shader.vs", "./shader/shader.fs");

	geo_node->set_shader_value("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
	geo_node->set_shader_value("light_pos", glm::vec3(1.0f, 1.0f, 2.0f));
	this->add_child(geo_node);
}


basic_lighting_node::~basic_lighting_node()
{
}
