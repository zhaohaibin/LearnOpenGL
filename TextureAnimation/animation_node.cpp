#include "animation_node.h"
#include "../base/geometry_node.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>

void animation_before_rendering_update_callback::do_update(node* p)
{
	geometry_node* geo_node = dynamic_cast<geometry_node*>(p);
	if (geo_node)
	{
		if (geo_node->get_id() == 0)
		{
			static double last_time = glfwGetTime();
			double ctime = glfwGetTime();
			float offset = (ctime - last_time) / 5.0;
			glm::vec3 offset_vec(offset, offset, 1.0);
			geo_node->set_shader_value("offset", offset_vec);
		}
		else if (geo_node->get_id() == 1 || geo_node->get_id() == 2)
		{
			static double last_time_2 = glfwGetTime();
			static float xoffset_2 = 0.0;
			double ctime = glfwGetTime();
			static bool left_to_right = true;
			if (left_to_right)
			{
				if (ctime - last_time_2 < 5.0)
					xoffset_2 = (ctime - last_time_2) / 5.0;
				else
				{
					last_time_2 = ctime;
					xoffset_2 = 1.0;
					left_to_right = false;
				}	
			}
			else
			{
				if (ctime - last_time_2 < 5.0)
					xoffset_2 = (5.0 - (ctime - last_time_2)) / 5.0;
				else
				{
					last_time_2 = ctime;
					xoffset_2 = 0.0;
					left_to_right = true;
				}
			}
			glm::vec3 offset_vec(xoffset_2, 0.0, 1.0);
			geo_node->set_shader_value("offset", offset_vec);
		}
		else if (geo_node->get_id() == 3)
		{
			static double last_time_3 = glfwGetTime();
			static float r = 0.0;
			double ctime = glfwGetTime();
			static bool left_to_right = true;
			if (left_to_right)
			{
				if (ctime - last_time_3 < 7.071)
					r = (ctime - last_time_3) / 5.0;
				else
				{
					last_time_3 = ctime;
					r = 1.4142;
					left_to_right = false;
				}
			}
			else
			{
				if (ctime - last_time_3 < 7.071)
					r = (7.071 - (ctime - last_time_3)) / 5.0;
				else
				{
					last_time_3 = ctime;
					r = 0.0;
					left_to_right = true;
				}
			}
			geo_node->set_shader_value("r", r);
		}

	}
}

float rect[] = {
	-1.0, 1.0, -0.2,
	-1.0, 0.0, -0.2,
	0.0, 0.0, -0.2,
	-1.0, 1.0, -0.2,
	0.0, 0.0, -0.2,
	0.0, 1.0, -0.2,
	};



float texture_coord[] =
{
	0.9, 0.0,
	0.9, 1.0,
	3.0, 1.0,
	0.9, 0.0,
	3.0, 1.0,
	3.0, 0.0
};

float rect_1[] = {
	0.0, 1.0, -0.2,
	0.0, 0.0, -0.2,
	1.0, 1.0, -0.2,
	1.0, 1.0, -0.2,
	0.0, 0.0, -0.2,
	1.0, 0.0, -0.2,
};
float texture_coord_1[] =
{
	0.0, 0.0,
	0.0, 1.0,
	1.0, 0.0,
	1.0, 0.0,
	0.0, 1.0,
	1.0, 1.0
};

animation_node::animation_node()
{
	m_callback = new animation_before_rendering_update_callback;
	geometry_node* p = new geometry_node;
	shader_file _file;
	_file.m_vertex_shader_file = "./shader/shader.vs";
	_file.m_frag_shader_file = "./shader/shader.fs";
	p->create_shader(_file);
	p->add_material("texture_1", "./shader/right.png");
	p->set_vertex(rect, sizeof(rect), 0);
	p->set_vertex_texture(texture_coord, sizeof(texture_coord), 1);
	p->set_primitive(GL_TRIANGLES);
	glm::vec3 offset_vec(0.0, 0.0, 1.0);
	p->set_shader_value("offset", offset_vec);
	p->set_before_rendering_update_callback(m_callback);
	p->set_id(0);
	add_child(p);

	p = new geometry_node;
	_file.m_vertex_shader_file = "./shader/shader_2.vs";
	_file.m_frag_shader_file = "./shader/shader_2.fs";
	p->create_shader(_file);
	p->add_material("texture_1", "./shader/right.png");
	p->add_material("texture_2", "./shader/wood.png");
	p->set_vertex(rect_1, sizeof(rect_1), 0);
	p->set_vertex_texture(texture_coord_1, sizeof(texture_coord_1), 1);
	p->set_primitive(GL_TRIANGLES);
	p->set_shader_value("offset", offset_vec);
	p->set_before_rendering_update_callback(m_callback);
	p->set_id(1);
	add_child(p);
// 
	glm::mat4 model(1.0);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
	p = new geometry_node(model);
	_file.m_vertex_shader_file = "./shader/shader_2.vs";
	_file.m_frag_shader_file = "./shader/shader_3.fs";
	p->create_shader(_file);
	p->add_material("texture_1", "./shader/right.png");
	p->add_material("texture_2", "./shader/wood.png");
	p->set_vertex(rect_1, sizeof(rect_1), 0);
	p->set_vertex_texture(texture_coord_1, sizeof(texture_coord_1), 1);
	p->set_primitive(GL_TRIANGLES);
	p->set_shader_value("offset", offset_vec);
	p->set_before_rendering_update_callback(m_callback);
	p->set_id(2);
	add_child(p);
// 
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 0.0f));
	p = new geometry_node(model);
	_file.m_vertex_shader_file = "./shader/shader_2.vs";
	_file.m_frag_shader_file = "./shader/shader_4.fs";
	p->create_shader(_file);
	p->add_material("texture_1", "./shader/right.png");
	p->add_material("texture_2", "./shader/wood.png");
	p->set_vertex(rect_1, sizeof(rect_1), 0);
	p->set_vertex_texture(texture_coord_1, sizeof(texture_coord_1), 1);
	p->set_primitive(GL_TRIANGLES);
	p->set_shader_value("r", 0.0f);
	p->set_before_rendering_update_callback(m_callback);
	p->set_id(3);
	add_child(p);
}


