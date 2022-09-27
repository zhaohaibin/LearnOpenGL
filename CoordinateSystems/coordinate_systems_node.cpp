#include "coordinate_systems_node.h"
#include "../base/cube.h"
#include "../base/line_node.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

coordinate_systems_node::coordinate_systems_node()
	: node()
{
	node_before_rendering_update_callback* callback = new coordinate_node_before_rendering_update_callback();

	glm::mat4 model = glm::mat4(1.0);
	//沿X方向移动-0.5，Y方向移动-0.3，Z方向移动1.0
	//model = glm::translate(model, glm::vec3(-0.6f, 0.0f, 1.0f));
	//沿Y轴旋转45度
	//model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	cube* p = new cube(1.0f, "../resource/texture/container.jpg", model);
	p->set_id(1);
	p->set_before_rendering_update_callback(callback);
	this->add_child(p);

	vector<point> points;
	points.push_back(point(0.0, -10.0, 0.0, 1.0, 0.0, 0.0, 1.0));
	points.push_back(point(0.0, 10.0, 0.0, 1.0, 0.0, 0.0, 1.0));
	points.push_back(point(-10.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0));
	points.push_back(point(10.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0));
	points.push_back(point(0.0, 0.0, -10.0, 0.0, 0.0, 1.0, 1.0));
	points.push_back(point(0.0, 0.0, 10.0, 0.0, 0.0, 1.0, 1.0));
	this->add_child(new line_node(points));
}


coordinate_systems_node::~coordinate_systems_node()
{
}

void coordinate_node_before_rendering_update_callback::do_update(node* p)
{
	if (p->get_id() == 1)
	{
		static glm::mat4 last = p->get_model_matrix();
		glm::mat4 model = p->get_model_matrix();
		last = glm::rotate(last, glm::radians(0.01f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(last, glm::vec3(1.0, 0.0, 0.0));
		p->set_model_matrix(model);
	}
	else if (p->get_id() == 2)
	{

	}
	else if (p->get_id() == 3)
	{

	}
}
