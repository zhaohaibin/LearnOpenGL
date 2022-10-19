#ifndef _GEOMETRY_NODE_H
#define _GEOMETRY_NODE_H
#include "node.h"
#include <map>

class geometry_node : public node
{
	struct shader_uniform_value
	{
		std::map<std::string, unsigned int> m_uint_value;
		std::map<std::string, float> m_float_value;
		std::map<std::string, glm::vec3> m_vec3_float_value;
		std::map<std::string, glm::vec4> m_vec4_float_value;
	};

public:
	geometry_node(glm::mat4 model_matrix = glm::mat4(1.0f));
	~geometry_node() {}

protected:
	virtual bool initialize() override;
	virtual void drawing() override;
public:
	void set_primitive(unsigned int primitive);
	void set_vertex(float* data, unsigned int length);
	void set_vertex_color(float* data, unsigned int length);
	void set_vertex_normal(float* data, unsigned int length);
	void set_shader_file(const std::string& vertex_shader_file, const std::string& frag_shader_file);

	void set_shader_value(const std::string& name, unsigned int value);
	void set_shader_value(const std::string& name, float value);
	void set_shader_value(const std::string& name, const glm::vec3& value);
	void set_shader_value(const std::string& name, const glm::vec4& value);
private:
	bool setup_vertex_array();
	bool setup_vertex_color_array();
	bool setup_vertex_normal_array();
	bool setup_shader();
	void use_shader();
	void update_mvp();
private:
	float* m_vertex_data;
	unsigned int m_vertex_data_length;

	float* m_vertex_color_data;
	unsigned int m_vertex_color_data_length;

	float* m_vertex_normal_data;
	unsigned int m_vertex_normal_data_length;

	unsigned int m_primitive;

	shader_uniform_value m_shader_uniform_value;
};

#endif //_GEOMETRY_NODE_H
