#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

/*
		渲染到一个不同的帧缓冲被叫做离屏渲染，要保证所有的渲染操作在主窗口中有视觉效果，
		我们需要再次激活默认帧缓冲，将它绑定到0
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		帧缓冲构建流程如下：
		step 1 : 创建帧缓冲
					unsigned int fbo;
					glGenFramebuffers(1, &fbo);
		step 2 : 绑定帧缓冲
					glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		step 3 : 设置帧缓冲的读写属性
		step 4 : 附加至少一个缓冲（颜色、深度、模板）
		step 5 : 至少添加一个颜色附件
		step 6 : 在完成所有的帧缓冲操作之后，不要忘记删除这个帧缓冲对象 
					glDeleteFramebuffers(1, &fbo);

		纹理附件:
					当把一个纹理附加到帧缓冲的时候，所有的渲染指令将会写入到这个纹理中，
					就想它是一个普通的颜色/深度或模板缓冲一样。使用纹理的优点是，所有渲
					染操作的结果将会被储存在一个纹理图像中，我们之后可以在着色器中很方便地使用它
*/


class framebuffer
{
public:
	framebuffer();
	~framebuffer();

public:
	void use();

	unsigned int get_texture();
private:

	void gen_framebuffer();
	/*
		创建一个纹理附件
		当把一个纹理附加到帧缓冲的时候，所有的渲染指令将会写入到这个纹理中，
		就想它是一个普通的颜色/深度或模板缓冲一样。使用纹理的优点是，所有渲
		染操作的结果将会被储存在一个纹理图像中，我们之后可以在着色器中很方便地使用它

		为帧缓冲创建一个纹理和创建一个普通的纹理差不多主要的区别就是，
		我们将维度设置为了屏幕大小（尽管这不是必须的），并且我们给纹理的 data 参数传递了 NULL 。
		对于这个纹理，我们仅仅分配了内存而没有填充它。填充这个纹理将会在我们渲染到帧缓冲之后来进行。
		同样注意我们并不关心环绕方式或多级渐远纹理，我们在大多数情况下都不会需要它们

		如果你想将你的屏幕渲染到一个更小或更大的纹理上，你需要（在渲染到你的帧缓冲之前）再次调用glViewport，
		使用纹理的新维度作为参数，否则只有一小部分的纹理或屏幕会被渲染到这个纹理上
	*/
	unsigned int create_texture_attachment();

	/*
		创建一个深度和模板缓冲
		创建为一个深度和模板附件渲染缓冲对象。我们将它的内部格式设置为
		GL_DEPTH24_STENCIL8，对我们来说这个精度已经足够了
	*/
	unsigned int create_depth_stencil_buffer();
private:
	unsigned int m_fbo;

	//颜色附件
	unsigned int m_texture;

	//深度和模板缓冲
	unsigned int m_depth_stencil_buffer;
};
#endif
