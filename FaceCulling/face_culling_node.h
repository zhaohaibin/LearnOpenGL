#ifndef _FACE_CULLING_NODE_H
#define _FACE_CULLING_NODE_H

#include "../base/node.h"

/*
默认值是GL_CCW，它代表的是逆时针的环绕顺序，另一个选项是GL_CW，它（显然）代表的是顺时针顺序
默认逆时针为正面，可以通过函数glFrontFace设置正面的环绕方式
glFrontFace(GL_CW); 将顺时针设置为正面
*/

class face_culling_node : public node
{
public:
	face_culling_node();

protected:
	virtual void do_render_childs();

private:
	node* m_face_culling_node;
	node* m_back_culling_node;
};
#endif //_FACE_CULLING_NODE_H
