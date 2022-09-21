#ifndef _FRAMEBUFFER_NODE_H
#define  _FRAMEBUFFER_NODE_H
#include "../base/node.h"
#include "../base/framebuffer.h"
#include "../base/system_env.h"

/*
	framebuffer_node 下的子节点将全部渲染到自定义的帧缓冲中，
	然后将该帧缓冲中的纹理附件作为framebuffer_node的纹理渲染到屏幕上
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


