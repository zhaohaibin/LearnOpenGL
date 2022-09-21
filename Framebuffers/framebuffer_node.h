#ifndef _FRAMEBUFFER_NODE_H
#define  _FRAMEBUFFER_NODE_H
#include "../base/node.h"
#include "../base/framebuffer.h"
#include "../base/system_env.h"

/*
	framebuffer_node �µ��ӽڵ㽫ȫ����Ⱦ���Զ����֡�����У�
	Ȼ�󽫸�֡�����е���������Ϊframebuffer_node��������Ⱦ����Ļ��
*/

namespace gl
{
	class shader;
}
class framebuffer_node : public node
{
public:
	framebuffer_node();
	~framebuffer_node();

	virtual void render();
	virtual void drawing();

protected:
	bool initialize() override;
private:
	gl::shader* m_shader;
	framebuffer* m_framebuffer;
	unsigned int m_texture_id;
	view_port m_vp;
};

#endif //_FRAMEBUFFER_NODE_H


