#ifndef _NODE_STATE_H
#define _NODE_STATE_H
#include <vector>
using namespace std;

class geometry_node;

class node_state
{
	friend class geometry_node;
public:
	node_state();
	~node_state();

	void enable_blend();
	void disable_blend();
	void set_blend_func(int sfactor, int dfactor);
	void set_blend_func(unsigned int sfactorRGB, unsigned int dfactorRGB, unsigned int sfactorAlpha, unsigned int dfactorAlpha);

protected:
	void do_set_state();

private:
	void do_set_blend();
private:
	bool m_enable_blend;
	vector<int> m_blend_fun;
};
#endif //_STATE_SET_H
