#include "framebuffer.h"
#include <iostream>
#include "system_env.h"
#include <glad/glad.h>

framebuffer::framebuffer()
{
	gen_framebuffer();
}

framebuffer::~framebuffer()
{

}

void framebuffer::use()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int framebuffer::get_texture()
{
	return m_texture;
}

void framebuffer::gen_framebuffer()
{
	//step 1 : 创建帧缓冲
	glGenFramebuffers(1, &m_fbo);

	//step 2 : 绑定帧缓冲，绑定之后所有的读取和写入帧缓冲的操作将会影响当前绑定的帧缓冲
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	
	//step 3 : 创建渲染缓冲区
	m_depth_stencil_buffer = create_depth_stencil_buffer();
	//step 4 : 附加渲染缓冲
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth_stencil_buffer);


	//创建一个颜色附件
	m_texture = create_texture_attachment();
	//将颜色附件附加到帧缓冲
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

	//检查帧缓冲的完整性
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int framebuffer::create_texture_attachment()
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	view_port vp = system_env::instance()->get_view_port();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, vp.m_width, vp.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

unsigned int framebuffer::create_depth_stencil_buffer()
{
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	view_port vp = system_env::instance()->get_view_port();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, vp.m_width, vp.m_height);
	return rbo;
}

