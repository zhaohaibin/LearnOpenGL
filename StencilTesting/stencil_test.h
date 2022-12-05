#ifndef _STENCIL_TEST_H
#define _STENCIL_TEST_H

#include "../base/node.h"

/*
	相关函数
	glStencilMask
		设置一个位掩码(Bitmask)，它将与将要写入缓冲的模板值进行AND运行。默认情况下
		设置的位掩码所有位都为1，不影响输出，但如果设置为0x00，写入缓冲的所有模板值最后都会变成0.

	glStencilFunc(GLenum func, GLint ref, GLuint mask)
		@func : 设置的模板测试函数。这个测试函数将会应用到已存储的模板值上和glStencilFun函数上的ref值上。
		@ref : 设置的模板测试的参考值。模板缓冲的内容将会与这个值进行比较。
		@mask : 设置一个掩码，它将会与参考值和存储的模板值在测试比较它们之前进行AND运行，初始情况下所有位都为1.

	glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass)
		@sfail : 模板测试失败时采取的行为
		@dpfail : 模板测试通过，但深度测试失败时采取的行为
		@dppass : 模板测试和深度测试都通过时采取的行为。

		行为							描述
		GL_KEEP					保持当前存储的模板值
		GL_ZERO					将模板值设置为0
		GL_REPLACE			将模板值设置为glStencilFunc函数设置的ref值
		GL_INCR					如果模板值下雨最大值，则将模板值加1
		GL_INCR_WRAP		与GL_INCR一样，但是，如果模板值超过了最大值则归零
		GL_DECR					如果模板值大于最小值，则将模板值减1
		GL_DECR_WRAP		与GL_DECR一样，但如果模板值小与0，则将其值设置为最大值。
		GL_INVERT				按位翻转当前的模板缓冲中
*/
class stencil_test : public node
{
public:
	stencil_test();

protected:
/*	virtual void do_render_childs();*/
};
#endif //_STENCIL_TEST_H
