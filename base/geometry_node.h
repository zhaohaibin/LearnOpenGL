#ifndef _GEOMETRY_NODE_H
#define _GEOMETRY_NODE_H
#include "node.h"
#include <map>
#include <vector>
#include "node_state.h"

class geometry_node : public node
{
	struct layout_data
	{
		inline layout_data(float* data, unsigned int length, unsigned int index, unsigned int step)
			: m_data(data)
			, m_length(length)
			, m_index(index)
			, m_step(step)
		{
		}
		float* m_data;
		unsigned int m_length;
		unsigned int m_index;
		unsigned int m_step;
		bool m_is_update;
	};
public:
	struct shader_uniform_value
	{
		std::map<std::string, unsigned int> m_uint_value;
		std::map<std::string, float> m_float_value;
		std::map<std::string, glm::vec3> m_vec3_float_value;
		std::map<std::string, glm::vec4> m_vec4_float_value;
	};

	struct material
	{
		std::string m_name;
		std::string m_file;
		int m_id;
	};

public:
	geometry_node(glm::mat4 model_matrix = glm::mat4(1.0f));
	~geometry_node() {}

protected:
	virtual bool initialize() override;
	virtual void drawing() override;
public:
	void set_primitive(unsigned int primitive);
	void set_vertex(float* data, unsigned int length, unsigned int layout_index);
	void update_vertex(float* data, unsigned int length);
	void set_vertex_color(float* data, unsigned int length, unsigned int layout_index);
	void set_vertex_normal(float* data, unsigned int length, unsigned int layout_index);
	void set_vertex_texture(float* data, unsigned int length, unsigned int layout_index, unsigned int step = 2);

	void set_layout_data(float* data, unsigned int length, unsigned int layout_index, unsigned int step = 2);
	//设置element
	// @data 指向索引数据
	// @length 索引个数
	void set_elements(unsigned int* data, unsigned int length);

	void set_draw_array(bool is_draw_array);
	void set_shader_value(const std::string& name, unsigned int value);
	void set_shader_value(const std::string& name, float value);
	void set_shader_value(const std::string& name, const glm::vec3& value);
	void set_shader_value(const std::string& name, const glm::vec4& value);

	void add_material(const std::string& name, const std::string file);
	void add_material(const material& _material);

	node_state* get_state_set();
private:
	bool setup_layout_data();
	bool setup_vertex_array();
	bool update_vertex_array();
	bool setup_vertex_color_array();
	bool setup_vertex_normal_array();
	bool setup_vertex_texture_array();
	bool setup_element();

	void update_uniform_value();
	void setup_texture();
	void do_use_shader();
	void update_mvp();
	void active_texture();
private:
	unsigned int m_vertex_vbo;
	float* m_vertex_data;
	unsigned int m_vertex_data_length;
	unsigned int m_vertex_layout_index;
	bool m_vertex_need_update;

	float* m_vertex_color_data;
	unsigned int m_vertex_color_data_length;
	unsigned int m_vertex_color_layout_index;

	float* m_vertex_normal_data;
	unsigned int m_vertex_normal_data_length;
	unsigned int m_vertex_normal_layout_index;

	float* m_vertex_texture_coord_data;
	unsigned int m_vertex_texture_coord_data_lenght;
	unsigned int m_vertex_texture_coord_layout_index;
	unsigned int m_vertex_texture_coord_step;

	//基于索引绘制的数据
	unsigned int* m_element_data;
	unsigned int m_element_count;

	unsigned int m_primitive;
	bool m_is_draw_arrays;

	shader_uniform_value m_shader_uniform_value;

	std::vector<material> m_materials;

	node_state m_state_set;

	std::vector<layout_data> m_layout_datas;
};

#endif //_GEOMETRY_NODE_H
