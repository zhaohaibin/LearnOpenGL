#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include "../base/system_env.h"
#include "../base/camera.h"
#include "../base/node.h"
#include "../base/rectangle_node.h"
#include "coordinate_systems_node.h"

float _deltaTime = 0.0f;
float _lastTime = 0.0f;
camera* _camera = system_env::instance()->get_camera();

void setup_scene(node*root)
{

}

void processInput(GLFWwindow *window)
{
	float cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_camera->process_keyboard(FORWARD, _deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_camera->process_keyboard(BACKWARD, _deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_camera->process_keyboard(LEFT, _deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_camera->process_keyboard(RIGHT, _deltaTime);
	}
}

bool _first_mouse = true;
double _mouse_x_pos = 0;
double _mouse_y_pos = 0;
bool _mouse_button_left_press = false;
bool _mouse_button_right_press = false;
void mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (_mouse_button_left_press == true)
	{
		if (_first_mouse)
		{
			_mouse_x_pos = xpos;
			_mouse_y_pos = ypos;
			_first_mouse = false;
		}
		float xoffset = float(xpos - _mouse_x_pos);
		float yoffset = float(_mouse_y_pos - ypos);
		_mouse_x_pos = xpos;
		_mouse_y_pos = ypos;

		_camera->process_mouse_move(MOUSE_LEFT_BTN, xoffset, yoffset);
	}
	else if (_mouse_button_right_press == true)
	{
		if (_first_mouse)
		{
			_mouse_x_pos = xpos;
			_mouse_y_pos = ypos;
			_first_mouse = false;
		}
		float xoffset = float(xpos - _mouse_x_pos);
		float yoffset = float(_mouse_y_pos - ypos);
		_mouse_x_pos = xpos;
		_mouse_y_pos = ypos;
		_camera->process_mouse_move(MOUSE_RIGHT_BTN, xoffset, yoffset);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT  && action == GLFW_PRESS)
	{
		if (_mouse_button_left_press == false)
		{
			_mouse_button_left_press = true;
			_first_mouse = true;
		}
		return;
	}
	_mouse_button_left_press = false;

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		if (_mouse_button_right_press == false)
		{
			_mouse_button_right_press = true;
			_first_mouse = true;
		}
		return;
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		//鼠标中键被按下
		return;
	}
	_mouse_button_right_press = false;

	_first_mouse = false;
}

void frame_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	view_port& vp = system_env::instance()->get_view_port();
	vp.m_width = width;
	vp.m_height = height;
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	_camera->process_mouse_scroll_wheel(yoffset);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	view_port& vp = system_env::instance()->get_view_port();
	GLFWwindow* window = glfwCreateWindow(vp.m_width, vp.m_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	_lastTime = (float)glfwGetTime();

	node* root = new node();
	root->add_child(new coordinate_systems_node);
	setup_scene(root);
	glEnable(GL_DEPTH_TEST);

	int rate = 0;
	time_t last_time = time(0);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		float currentFrame = (float)glfwGetTime();
		_deltaTime = currentFrame - _lastTime;
		_lastTime = currentFrame;

		processInput(window);

		root->render();
		glfwSwapBuffers(window);
		glfwPollEvents();
		++rate;
		time_t ctime = time(0);
		if (ctime - last_time >= 1)
		{
			std::cout << rate << " frame / s" << std::endl;
			last_time = ctime;
			rate = 0;
		}
	}
	glfwTerminate();
	return 0;
}