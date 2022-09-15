#ifndef _NODE_H
#define _NODE_H

#include <list>
#include <glm/glm.hpp>
class node
{
public:
	node();
	virtual ~node();

	void add_child(node* p);

	void remove_child(node* p);


	virtual void render();

	glm::mat4 get_projection_matrix4();
protected:
	virtual bool initialize();
	virtual void drawing();

	void do_render_childs();
protected:
	unsigned int m_vao;
	unsigned int m_ebo;
private:
	
	bool m_init;
	typedef  std::list<node*> childs;

	childs m_childs;


};
#endif //_NODE_H
