#ifndef _FRAMEBUFFER_NODE_H
#define  _FRAMEBUFFER_NODE_H
#include "../base/node.h"
#include "../base/framebuffer.h"

/*
	framebuffer_node �µ��ӽڵ㽫ȫ����Ⱦ���Զ����֡�����У�
	Ȼ�󽫸�֡�����е���������Ϊframebuffer_node��������Ⱦ����Ļ��
*/
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
	bool m_init;
	framebuffer m_framebuffer;
};

#endif //_FRAMEBUFFER_NODE_H


