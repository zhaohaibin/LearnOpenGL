#include "sprite_node.h"
#include "../base/point_sprite.h"
#include "GLFW/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>
//float data[] = { 0.0f,0.0f,0.0f, 0.2f,0.0f,-1.5f, 0.8f,0.0f,-3.0f };
float* data = new float[3 * 12000];
void sprite_node_update_callback::do_update(node* p)
{
	point_sprite* sprite = dynamic_cast<point_sprite*>(p);
	double time =  glfwGetTime();
	srand(time);
	int index = 0;
	for (int i = 0; i < 12000;)
	{
		if (index == 0)
		{
			data[i++] = sin((time+i*i) / 5.0);
			data[i++] = cos((time + i*i) / 5.0);
			data[i++] = sin((time + i*i) / 5.0);
		}
		else if (index == 1)
		{
			data[i++] = cos((time + i*i) / 5.0);
			data[i++] = sin((time + i*i) / 5.0);
			data[i++] = cos((time + i*i) / 5.0);
		}
		else
		{
			data[i++] = sin((time + i*i) / 5.0);
			data[i++] = sin((time + i*i) / 5.0);
			data[i++] = cos((time + i*i) / 5.0);
		}
		if (index > 1)
			index = 0;
		else
			index++;
	}
	sprite->update_vertex(data, 3 * 12000 * sizeof(float));
}

sprite_node::sprite_node()
{
	point_sprite* _point_prite = new point_sprite(1.0);
	_point_prite->set_vertex(data, 100*3*sizeof(float), 0);
	_point_prite->set_vertex_shader_file("./shader/shader.vs");
	_point_prite->set_frag_shader_file("./shader/shader.fs");
	_point_prite->add_material("texture_1", "./resources/awesomeface.png");
	_point_prite->set_before_rendering_update_callback(new sprite_node_update_callback());
	add_child(_point_prite);
	//return;
	glm::mat4 model(1.0);
	model = glm::translate(model, glm::vec3(-0.2f, 0.3f, 1.0f));
	_point_prite = new point_sprite(1.0, model);
	_point_prite->set_vertex(data, 100 * 3 * sizeof(float), 0);
	_point_prite->set_vertex_shader_file("./shader/shader.vs");
	_point_prite->set_frag_shader_file("./shader/shader.fs");
	_point_prite->add_material("texture_1", "./resources/awesomeface.png");
	_point_prite->set_before_rendering_update_callback(new sprite_node_update_callback());
	add_child(_point_prite);
}