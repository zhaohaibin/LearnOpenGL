#ifndef _system_env_h
#define _system_env_h

struct view_port
{
	view_port();
	unsigned int m_width;
	unsigned int m_height;
};

class camera;
class system_env
{
protected:
	system_env();
public:
	static system_env* instance();
	view_port& get_view_port();
	camera* get_camera();
private:
	static system_env* m_instance;
	view_port m_view_port;
	camera* m_camera;
};
#endif //_system_env_h