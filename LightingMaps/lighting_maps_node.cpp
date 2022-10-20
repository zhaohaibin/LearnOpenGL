#include "lighting_maps_node.h"
#include "../base/geometry_node.h"
#include "../base/system_env.h"
#include "../base/camera.h"
#include <glad/glad.h>

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

lighting_maps_node::lighting_maps_node()
{
	float vertices[] = {
		// positions
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	float normals[] = {
		// normals
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,

		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,

		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
	};

	float texture[] = {
		// texture coords
		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,

		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,

		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,
		1.0f,  0.0f,

		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,
		1.0f,  0.0f,

		0.0f,  1.0f,
		1.0f,  1.0f,
		1.0f,  0.0f,
		1.0f,  0.0f,
		0.0f,  0.0f,
		0.0f,  1.0f,

		0.0f,  1.0f,
		1.0f,  1.0f,
		1.0f,  0.0f,
		1.0f,  0.0f,
		0.0f,  0.0f,
		0.0f,  1.0f
	};

	geometry_node* geo_node = new geometry_node;
	geo_node->set_before_rendering_update_callback(new geometry_node_before_rendering_update_callback());
	float* vertex_data = new float[3 * 6 * 6];
	memcpy(vertex_data, vertices, 3 * 6 * 6 * sizeof(float));
	geo_node->set_vertex(vertex_data, 3 * 6 * 6 * sizeof(float), 0);

	float* vertex_normal_data = new float[3 * 6 * 6];
	memcpy(vertex_normal_data, normals, 3 * 6 * 6 * sizeof(float));
	geo_node->set_vertex_normal(vertex_normal_data, 3 * 6 * 6 * sizeof(float), 1);

	float* vertex_texture_data = new float[2 * 6 * 6];
	memcpy(vertex_texture_data, texture, 2 * 6 * 6 * sizeof(float));
	geo_node->set_vertex_texture(vertex_texture_data, 2 * 6 * 6 * sizeof(float), 2);

	geo_node->set_vertex_shader_file("./resource/shader/shader.vs");
	geo_node->set_frag_shader_file("./resource/shader/shader.fs");
	geo_node->set_shader_value("light", glm::vec3(1.0f, 1.0f, 1.0f));
	geo_node->set_shader_value("light_pos", glm::vec3(1.0f, 1.0f, 2.0f));

	geo_node->add_material("diffuse", "./resource/texture/container2.png");
	geo_node->add_material("specular", "./resource/texture/container2_specular.png");

	geo_node->set_primitive(GL_TRIANGLES);
	this->add_child(geo_node);
}

