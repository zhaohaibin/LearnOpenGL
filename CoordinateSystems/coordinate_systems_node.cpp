#include "coordinate_systems_node.h"
#include "../base/cube.h"
#include "../base/line_node.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "../base/rectangle_node.h"

coordinate_systems_node::coordinate_systems_node()
	: node()
{
	node_before_rendering_update_callback* callback = new coordinate_node_before_rendering_update_callback();

	glm::mat4 model = glm::mat4(1.0);
	//沿X方向移动-0.5，Y方向移动-0.3，Z方向移动1.0
	model = glm::translate(model, glm::vec3(-2.0f, 2.0f, -1.0f));
	//沿Y轴旋转45度
	//model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	cube* p = new cube(1.0f, "../resource/texture/container.jpg", model);
	p->set_id(1);
	p->set_before_rendering_update_callback(callback);
	this->add_child(p);

	//添加XYZ坐标
	vector<point> points;
	points.push_back(point(0.0, -10.0, 0.0, 1.0, 0.0, 0.0, 1.0));
	points.push_back(point(0.0, 10.0, 0.0, 1.0, 0.0, 0.0, 1.0));
	points.push_back(point(-10.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0));
	points.push_back(point(10.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0));
	points.push_back(point(0.0, 0.0, -10.0, 0.0, 0.0, 1.0, 1.0));
	points.push_back(point(0.0, 0.0, 10.0, 0.0, 0.0, 1.0, 1.0));
	this->add_child(new line_node(points));

	model = glm::mat4(1.0);
	node* p_node = new rectangle_node(0.5, 0.5, "../resource/texture/albedo.png", model);
	p_node->set_id(2);
	p_node->set_before_rendering_update_callback(callback);
	this->add_child(p_node);

	model = glm::mat4(1.0);
	//沿X方向移动-0.5，Y方向移动-0.3，Z方向移动1.0
	model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
	p_node = new cube(1.0, "../resource/texture/container.jpg", model);
	p_node->set_id(3);
	p_node->set_before_rendering_update_callback(callback);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 0.75f, 0.0f));
	node* child_node = new cube(0.5, "../resource/texture/container2.png", model);
	child_node->set_id(4);
	child_node->set_before_rendering_update_callback(callback);
	p_node->add_child(child_node);
	this->add_child(p_node);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
	node* child_node2 = new cube(0.2, "../resource/texture/container2.png", model);
	child_node->add_child(child_node2);
	child_node2->set_id(5);
	child_node2->set_before_rendering_update_callback(callback);
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
		last = glm::rotate(last, glm::radians(0.01f), glm::vec3(1.0f, 1.0f, 0.0f));
		model = last;
		model = glm::translate(last, glm::vec3(-1.0, 1.0, 0.0));
		p->set_model_matrix(model);
	}
	else if (p->get_id() == 2)
	{
		static glm::mat4 last_2 = p->get_model_matrix();
		glm::mat4 model = p->get_model_matrix();
		last_2 = glm::rotate(last_2, glm::radians(0.02f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = last_2;
		model = glm::translate(model, glm::vec3(0.25, 0.25, 0.0));
		p->set_model_matrix(model);
	}
	else if (p->get_id() == 3)
	{
		static glm::mat4 last_3 = p->get_model_matrix();
		glm::mat4 model = p->get_model_matrix();
		last_3 = glm::rotate(last_3, glm::radians(0.02f), glm::vec3(	1.0f, 1.0f, 0.0f));
		model = last_3;
		model = glm::translate(model, glm::vec3(1.0, 0.0, 0.0));
		p->set_model_matrix(model);
	}
	else if (p->get_id() == 4)
	{
		static glm::mat4 last_4 = p->get_model_matrix();
		glm::mat4 model = p->get_model_matrix();
		last_4 = glm::rotate(last_4, glm::radians(-0.04f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = last_4;
		p->set_model_matrix(model);
	}
	else if (p->get_id() == 5)
	{
		static glm::mat4 last_5 = p->get_model_matrix();
		glm::mat4 model = p->get_model_matrix();
		last_5 = glm::rotate(last_5, glm::radians(-0.04f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = last_5;
		p->set_model_matrix(model);
	}
}
