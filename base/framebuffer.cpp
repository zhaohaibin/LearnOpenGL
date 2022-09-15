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
}

void framebuffer::gen_framebuffer()
{
	//step 1 : ����֡����
	glGenFramebuffers(1, &m_fbo);

	//step 2 : ��֡����
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	//step 3 : ������Ⱦ������
	m_depth_stencil_buffer = create_depth_stencil_buffer();

	//step 4 : ������Ⱦ����
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth_stencil_buffer);

	//����һ����ɫ����
	m_texture = create_texture_attachment();

	//����ɫ�������ӵ�֡����
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

	//���֡�����������
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
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	return rbo;
}

