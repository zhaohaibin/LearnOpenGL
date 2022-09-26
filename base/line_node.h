#ifndef _LINE_NODE_H
#define _LINE_NODE_H

#include <vector>
#include <glm/glm.hpp>

#include "node.h"

struct point
{
	inline point(float x, float y, float z, float r, float g, float b, float a)
		: m_x(x), m_y(y), m_z(z), m_r(r), m_g(g), m_b(b), m_a(a)
	{
	
	}
	float m_x;
	float m_y;
	float m_z;

	float m_r;
	float m_g;
	float m_b;
	float m_a;
};

class line_node : public node
{
public:
	line_node(const std::vector<point>& points);

protected:
	virtual bool initialize() override;
	virtual void drawing() override;

private:
	std::vector<point> m_points;
};
#endif //_LINE_NODE_H
