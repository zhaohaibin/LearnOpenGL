#ifndef _FACE_CULLING_NODE_H
#define _FACE_CULLING_NODE_H

#include "../base/node.h"

/*
Ĭ��ֵ��GL_CCW�������������ʱ��Ļ���˳����һ��ѡ����GL_CW��������Ȼ���������˳ʱ��˳��
Ĭ����ʱ��Ϊ���棬����ͨ������glFrontFace��������Ļ��Ʒ�ʽ
glFrontFace(GL_CW); ��˳ʱ������Ϊ����
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
