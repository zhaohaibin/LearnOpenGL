#ifndef _NODE_H
#define _NODE_H

#include <list>
#include <string>
#include <vector>
#include <glm/glm.hpp>

class node;
class node_before_rendering_update_callback
{
	friend class node;
public:
	node_before_rendering_update_callback() {}
	virtual ~node_before_rendering_update_callback() {}
protected:
	virtual void do_update(node* p) = 0;
};

namespace gl
{
	class shader;
}

struct shader_file
{
	std::string m_vertex_shader_file;
	std::string m_frag_shader_file;
};

class node
{
public:
	node( glm::mat4 model_matrix = glm::mat4(1.0f));
	virtual ~node();

	void add_child(node* p);
	void remove_child(node* p);
	void set_before_rendering_update_callback(node_before_rendering_update_callback* p);
	void set_id(unsigned int id);
	unsigned int get_id();
	virtual void render();

	void set_model_matrix(glm::mat4 matrix);
	glm::mat4 get_model_matrix();
	glm::mat4 get_merge_model_matrix();
	glm::mat4 get_projection_matrix4();

	unsigned int create_shader(const shader_file& file);
	void switch_shader(unsigned char index);
protected:
	virtual bool initialize();
	virtual void drawing();
	virtual void do_render_childs();

	bool setup_shader();
	virtual void update_uniform_value();
	virtual void setup_texture();

	//获取当前选则的shader
	gl::shader* get_shader();

	void use_shader();

	void un_use_shader();
private:
	void do_set_matrix();
	glm::mat4 get_ancestors_model();
protected:
	unsigned int m_vao;
	unsigned int m_ebo;
	bool m_model_matrix_need_update;
	glm::mat4 m_model_matrix;

	bool m_init;
private:
	node* m_parent_node;
	unsigned int m_id;

	typedef  std::list<node*> childs;
	childs m_childs;
	node_before_rendering_update_callback* m_before_rendering_update_callback;


	//支持多个着色器
	std::vector<shader_file> m_shader_files;
	std::vector<gl::shader*> m_shaders;
	unsigned char m_curent_shader_index;
};
#endif //_NODE_H
