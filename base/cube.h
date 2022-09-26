#ifndef _CUBE_H
#define _CUBE_H

#include "node.h"
#include <glm/glm.hpp>
#include "../base/shader.h"

class cube : public node
{
public:
	cube(float width, const string& texture_image, const glm::mat4& model);
	~cube();

public:
	virtual bool initialize() override;
	virtual void drawing() override;

private:
	void init();
	 int gen_buffer_data(float* data);
private:
	float m_width;
	string m_texture_image;
	bool m_init;
	unsigned int* m_indices;
	unsigned int m_texture;
	gl::shader* m_shader;
};

#endif //_CUBE_H
