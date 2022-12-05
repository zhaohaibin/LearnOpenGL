#ifndef _STENCIL_TEST_H
#define _STENCIL_TEST_H

#include "../base/node.h"

/*
	��غ���
	glStencilMask
		����һ��λ����(Bitmask)�������뽫Ҫд�뻺���ģ��ֵ����AND���С�Ĭ�������
		���õ�λ��������λ��Ϊ1����Ӱ����������������Ϊ0x00��д�뻺�������ģ��ֵ��󶼻���0.

	glStencilFunc(GLenum func, GLint ref, GLuint mask)
		@func : ���õ�ģ����Ժ�����������Ժ�������Ӧ�õ��Ѵ洢��ģ��ֵ�Ϻ�glStencilFun�����ϵ�refֵ�ϡ�
		@ref : ���õ�ģ����ԵĲο�ֵ��ģ�建������ݽ��������ֵ���бȽϡ�
		@mask : ����һ�����룬��������ο�ֵ�ʹ洢��ģ��ֵ�ڲ��ԱȽ�����֮ǰ����AND���У���ʼ���������λ��Ϊ1.

	glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass)
		@sfail : ģ�����ʧ��ʱ��ȡ����Ϊ
		@dpfail : ģ�����ͨ��������Ȳ���ʧ��ʱ��ȡ����Ϊ
		@dppass : ģ����Ժ���Ȳ��Զ�ͨ��ʱ��ȡ����Ϊ��

		��Ϊ							����
		GL_KEEP					���ֵ�ǰ�洢��ģ��ֵ
		GL_ZERO					��ģ��ֵ����Ϊ0
		GL_REPLACE			��ģ��ֵ����ΪglStencilFunc�������õ�refֵ
		GL_INCR					���ģ��ֵ�������ֵ����ģ��ֵ��1
		GL_INCR_WRAP		��GL_INCRһ�������ǣ����ģ��ֵ���������ֵ�����
		GL_DECR					���ģ��ֵ������Сֵ����ģ��ֵ��1
		GL_DECR_WRAP		��GL_DECRһ���������ģ��ֵС��0������ֵ����Ϊ���ֵ��
		GL_INVERT				��λ��ת��ǰ��ģ�建����
*/
class stencil_test : public node
{
public:
	stencil_test();

protected:
/*	virtual void do_render_childs();*/
};
#endif //_STENCIL_TEST_H
