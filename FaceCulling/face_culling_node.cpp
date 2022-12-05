#include "face_culling_node.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "../base/entity/cube.h"
using namespace entity;
face_culling_node::face_culling_node()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(-0.2f, 0.0f, -1.0f));
	m_face_culling_node = new cube(0.3, "../resource/texture/container.jpg", model);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.2f, 0.0f, -1.0f));
	m_back_culling_node = new cube(0.3, "../resource/texture/container.jpg", model);
}

void face_culling_node::do_render_childs()
{
	//�������޳�
	glEnable(GL_CULL_FACE);

	//����Ϊ�����޳�
	glCullFace(GL_FRONT);
	m_face_culling_node->render();
	//����Ϊ�����޳�
	glCullFace(GL_BACK);
	m_back_culling_node->render();

	//GL_FRONT_AND_BACK ����ͱ���ȫ���޳�
}

