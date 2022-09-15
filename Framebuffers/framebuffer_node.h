#ifndef _FRAMEBUFFER_NODE_H
#define  _FRAMEBUFFER_NODE_H
#include "../base/node.h"
#include "../base/framebuffer.h"

/*
	framebuffer_node 下的子节点将全部渲染到自定义的帧缓冲中，
	然后将该帧缓冲中的纹理附件作为framebuffer_node的纹理渲染到屏幕上
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


