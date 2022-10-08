#include "camera.h"
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

camera::camera(glm::vec3 position /*= glm::vec3(0.0f, 0.0f, 0.0f)*/, 
	glm::vec3 up /*= glm::vec3(0.0f, 1.0f, 0.0f)*/, 
	float yaw /*= YAW*/, float pitch /*= PITCH*/)
	: m_front(glm::vec3(0.0f, 0.0f, -1.0f))
	, m_speed(SPEED)
	, m_mouse_sensitivity(SENSITIVITY)
	, m_zoom(ZOOM)
	, m_position(position)
	, m_worldUp(up)
	, m_yaw(yaw)
	, m_pitch(pitch)
{
	update_camera_vectors();
}

glm::mat4 camera::get_view_matrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::vec3 camera::get_position()
{
	return m_position;
}

glm::vec3 camera::get_front()
{
	return m_front;
}

float camera::get_filed_view()
{
	return m_zoom;
}

void camera::process_keyboard(camera_move_event event, float delta_time)
{
	float velocity = m_speed*delta_time;
	if (event == FORWARD)
		m_position += m_front*velocity;
	if (event == BACKWARD)
		m_position -= m_front*velocity;
	if (event == LEFT)
		m_position -= m_right*velocity;
	if (event == RIGHT)
		m_position += m_right*velocity;
}

void camera::process_mouse_movent(float xoffset, float yoffset, bool constrain_pitch /*=true*/)
{
	xoffset *= m_mouse_sensitivity*0.1;
	yoffset *= m_mouse_sensitivity*0.1;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (constrain_pitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	//更新相机坐标轴（前，右，上）
	update_camera_vectors();
}

void camera::process_mouse_move(mouse_press_button btn, float xoffset, float yoffset)
{
	if (btn == MOUSE_LEFT_BTN)
		do_process_mouse_left_btn_press_move(xoffset, yoffset, true);
	else if (btn == MOUSE_RIGHT_BTN)
		do_process_mouse_right_btn_press_move(xoffset, yoffset);
}

void camera::process_mouse_scroll_wheel(float yoffset)
{
	m_zoom -= yoffset;
	if (m_zoom < 1.0f)
		m_zoom = 1.0f;
	if (m_zoom > 45.0f)
		m_zoom = 45.0f;
}

void camera::update_camera_vectors()
{
	//根据俯仰角和偏航角计算目标点
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw))*cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw))*cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	//计算相机右轴和上轴
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void camera::do_process_mouse_left_btn_press_move(float xoffset, float yoffset, bool constrain_pitch /*= true*/)
{
	xoffset *= m_mouse_sensitivity;
	yoffset *= m_mouse_sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (constrain_pitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	//更新相机坐标轴（前，右，上）
	update_camera_vectors();
}

void camera::do_process_mouse_right_btn_press_move(float xoffset, float yoffset)
{
	xoffset *= m_mouse_sensitivity;
	yoffset *= m_mouse_sensitivity;

	glm::mat4 mat_y(1.0f);
	mat_y = glm::rotate(mat_y, glm::radians(xoffset), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 mat_x(1.0f);
	mat_x = glm::rotate(mat_y, glm::radians(yoffset), glm::vec3(1.0f, 0.0f, 0.0f));

	m_position = glm::vec3(mat_y * mat_x * glm::vec4(m_position, 1.0f));
}
