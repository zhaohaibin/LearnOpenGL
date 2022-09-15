#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum camera_move_event
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

enum mouse_press_button
{
	MOUSE_LEFT_BTN,
	MOUSE_RIGHT_BTN
};

//Æ«º½½Ç
const float YAW = -90.0f;
//¸©Ñö½Ç
const float PITCH = 0.0f;
//ÒÆ¶¯ËÙ¶È
const float SPEED = 2.5f;
//ÁéÃô¶È
const float SENSITIVITY = 0.1f;

const float ZOOM = 45.0f;

class camera
{
public:
	camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), 
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float yaw = YAW, float pitch = PITCH);

	glm::mat4 get_view_matrix();
	glm::vec3 get_position();
	glm::vec3 get_front();
	void process_keyboard(camera_move_event event, float delta_time);
	void process_mouse_movent(float xoffset, float yoffset, bool constrain_pitch =true);
	void process_mouse_move(mouse_press_button btn, float xoffset, float yoffset);
	void process_mouse_scroll_wheel(float yoffset);
private:
	void update_camera_vectors();
	void do_process_mouse_left_btn_press_move(float xoffset, float yoffset, bool constrain_pitch = true);
	void do_process_mouse_right_btn_press_move(float xoffset, float yoffset);
private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	//euler angles
	float m_yaw;
	float m_pitch;

	float m_speed;
	float m_mouse_sensitivity;
	float m_zoom;
};
#endif //_CAMERA_H
