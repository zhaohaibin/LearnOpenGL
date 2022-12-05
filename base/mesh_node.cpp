#include "mesh_node.h"
#include <glad/glad.h>
#include "shader.h"
#include <string>
#include "texture_loader.h"
#include "system_env.h"
#include "camera.h"
using namespace std;

mesh::mesh()
: m_vertex_numbers(0)
, m_vertex(nullptr)
, m_normal(nullptr)
, m_texcoords(nullptr)
, m_tangent(nullptr)
, m_bittangent(nullptr)
, m_index(nullptr)
{

}

mesh_node::mesh_node(mesh* _mesh)
	: m_mesh(_mesh)
{

}

bool mesh_node::initialize()
{
// 	if (m_mesh->m_vertex == nullptr)
// 		return false;
// 
// 	//顶点数组对象
// 	glGenVertexArrays(1, &m_vao);
// 	glBindVertexArray(m_vao);
// 
// 	//顶点缓冲对象
// 	unsigned int vbo;
// 	glGenBuffers(1, &vbo);
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, m_mesh->m_vertex_numbers*sizeof(float)*3, m_mesh->m_vertex, GL_STATIC_DRAW);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 	glEnableVertexAttribArray(0);
// 
// 	if (m_mesh->m_normal != nullptr)
// 	{
// 		glGenBuffers(1, &vbo);
// 		glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 		glBufferData(GL_ARRAY_BUFFER, m_mesh->m_vertex_numbers * sizeof(float) * 3, m_mesh->m_normal, GL_STATIC_DRAW);
// 		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 		glEnableVertexAttribArray(1);
// 	}
// 	if (m_mesh->m_texcoords != nullptr)
// 	{
// 		glGenBuffers(1, &vbo);
// 		glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 		glBufferData(GL_ARRAY_BUFFER, m_mesh->m_vertex_numbers * sizeof(float) * 3, m_mesh->m_texcoords, GL_STATIC_DRAW);
// 		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 		glEnableVertexAttribArray(2);
// 	}
// 	if (m_mesh->m_tangent != nullptr)
// 	{
// 		glGenBuffers(1, &vbo);
// 		glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 		glBufferData(GL_ARRAY_BUFFER, m_mesh->m_vertex_numbers * sizeof(float) * 3, m_mesh->m_tangent, GL_STATIC_DRAW);
// 		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 		glEnableVertexAttribArray(3);
// 	}
// 	if (m_mesh->m_bittangent != nullptr)
// 	{
// 		glGenBuffers(1, &vbo);
// 		glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 		glBufferData(GL_ARRAY_BUFFER, m_mesh->m_vertex_numbers * sizeof(float) * 3, m_mesh->m_bittangent, GL_STATIC_DRAW);
// 		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 		glEnableVertexAttribArray(4);
// 	}
// 
// 	glGenBuffers(1, &m_ebo);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_mesh->m_index_count, m_mesh->m_index, GL_STATIC_DRAW);
// 
// 	if (m_shader == nullptr)
// 	{
// 		const string path = "D:/Workspace/opengl/WorkSpace/LearnOpenGL/base/";
// 		m_shader = new gl::shader(path + "/shader/mesh_node/shader.vs", path + "/shader/mesh_node/shader.fs");
// 		string error;
// 		if (m_shader->initialize(error) == false)
// 			return false;
// 	}
// 
// 	m_shader->use();
// 	//设置纹理
// 	unsigned int diffuseNr = 1;
// 	unsigned int specularNr = 1;
// 	unsigned int normalNr = 1;
// 	unsigned int heightNr = 1;
// 	for (int i = 0; i < m_mesh->m_textures.size(); ++i)
// 	{
// 		texture _texture = m_mesh->m_textures[i];
// 		int num = 0;
// 		if (_texture.m_type == "texture_diffuse")
// 			num = diffuseNr++;
// 		else if (_texture.m_type == "texture_specular")
// 			num = specularNr++;
// 		else if (_texture.m_type == "texture_normal")
// 			num = normalNr++;
// 		else if (_texture.m_type == "texture_height")
// 			num = heightNr++;
// 		string  name = _texture.m_type + "_" + std::to_string(num);
// 		unsigned int id = m_mesh->m_textures[i].m_id;
// 		m_shader->set_int(name, i);
// 	}
	return true;
}

void mesh_node::drawing()
{
// 	glBindVertexArray(m_vao);
// 	m_shader->use();
// 	for (int i = 0; i < m_mesh->m_textures.size(); ++i)
// 	{
// 		glActiveTexture(GL_TEXTURE0 + i);
// 		glBindTexture(GL_TEXTURE_2D, m_mesh->m_textures[i].m_id);
// 	}
// 
// 	
// 	glm::mat4 view(1.0f);
// 	view = system_env::instance()->get_camera()->get_view_matrix();
// 	m_shader->set_matrix4("view", view);
// 
// 	glm::mat4 projection = get_projection_matrix4();
// 	m_shader->set_matrix4("projection", projection);
// 
// 	m_shader->set_matrix4("model", /*m_model_matrix*/get_merge_model_matrix());
// 
// 	
// 
// 	
// 	glDrawElements(GL_TRIANGLES, m_mesh->m_index_count, GL_UNSIGNED_INT, 0);
// 	glBindVertexArray(0);
// 
// 	glActiveTexture(GL_TEXTURE0);
}
