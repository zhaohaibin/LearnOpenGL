#include "sprite_node.h"
#include "../base/point_sprite.h"
#include "GLFW/glfw3.h"

float data[] = { 0.0f,0.0f,0.0f, 0.2f,0.0f,-1.5f, 0.8f,0.0f,-3.0f };
void sprite_node_update_callback::do_update(node* p)
{
	point_sprite* sprite = dynamic_cast<point_sprite*>(p);
	double time =  glfwGetTime();
	srand(time);
	int index = 0;
	for (int i = 0; i < sizeof(data) / sizeof(float);)
	{
		if (index == 0)
		{
			data[i++] = sin(time / 5.0);
			data[i++] = cos(time / 5.0);
			data[i++] = sin(time / 5.0);
		}
		else if (index == 1)
		{
			data[i++] = cos(time / 5.0);
			data[i++] = sin(time / 5.0);
			data[i++] = cos(time / 5.0);
		}
		else
		{
			data[i++] = sin(time / 5.0);
			data[i++] = sin(time / 5.0);
			data[i++] = cos(time / 5.0);
		}
		index++;
	}
	sprite->update_vertex(data, sizeof(data));
}

sprite_node::sprite_node()
{
	point_sprite* _point_prite = new point_sprite(1.0);
	_point_prite->set_vertex(data, sizeof(data), 0);
	_point_prite->set_vertex_shader_file("./shader/shader.vs");
	_point_prite->set_frag_shader_file("./shader/shader.fs");
	_point_prite->add_material("texture_1", "./resources/awesomeface.png");
	_point_prite->set_before_rendering_update_callback(new sprite_node_update_callback());
	add_child(_point_prite);
	return;
	_point_prite = new point_sprite(1.0);
	float data_1[] = { 0.3f, 0.0f, 0.0f };
	float* vertex_data_1 = new float[sizeof(data_1)];
	_point_prite->set_vertex(data_1, sizeof(data_1), 0);
}