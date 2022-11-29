#include "animation_node.h"
#include "../base/geometry_node.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"

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
		else if (geo_node->get_id() == 1)
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
	p->set_vertex_shader_file("./shader/shader.vs");
	p->set_frag_shader_file("./shader/shader.fs");
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
	p->set_vertex_shader_file("./shader/shader_2.vs");
	p->set_frag_shader_file("./shader/shader_2.fs");
	p->add_material("texture_1", "./shader/right.png");
	p->add_material("texture_2", "./shader/wood.png");
	p->set_vertex(rect_1, sizeof(rect_1), 0);
	p->set_vertex_texture(texture_coord_1, sizeof(texture_coord_1), 1);
	p->set_primitive(GL_TRIANGLES);
	p->set_shader_value("offset", offset_vec);
	p->set_before_rendering_update_callback(m_callback);
	p->set_id(1);
	add_child(p);
}


