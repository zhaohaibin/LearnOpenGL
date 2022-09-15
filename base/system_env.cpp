#include "system_env.h"
#include "camera.h"
view_port::view_port() : m_width(800)
, m_height(600)
{

}

system_env* system_env::m_instance = new system_env();
system_env::system_env()
	: m_camera(new camera)
{

}

system_env* system_env::instance()
{
	return m_instance;
}

view_port& system_env::get_view_port()
{
	return m_view_port;
}

camera* system_env::get_camera()
{
	return m_camera;
}

