#include "cube.h"
#include <glad/glad.h>

namespace entity
{
	cube::cube(float width, const string& texture_image, glm::mat4 model_matrix/* = glm::mat4(1.0f)*/)
		: geometry_node(model_matrix)
		, m_width(width)
		, m_texture_image(texture_image)
		, m_init(true)
		, m_shader(nullptr)
	{
		set_primitive(GL_TRIANGLES);
		shader_file _file;
		const string path = "D:/Workspace/opengl/WorkSpace/LearnOpenGL/base/";
		_file.m_vertex_shader_file = path + "/shader/cube/shader.vs";
		_file.m_frag_shader_file = path + "/shader/cube/shader.fs";
		create_shader(_file);

		add_material("texture1", m_texture_image);
		//∂•µ„ª∫≥Â∂‘œÛ
		float* vertex_data;
		int size = gen_vertex_data(&vertex_data);
		set_vertex(vertex_data, size, 0);

		float* texture_coord_data;
		size = gen_texture_coord_data(&texture_coord_data);
		set_vertex_texture(texture_coord_data, size, 1);

		unsigned int temp[] = {
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7,
			8, 9, 10,
			8, 10, 11,
			12, 13, 14,
			12, 14, 15,
			16, 17, 18,
			16, 18, 19,
			20, 21, 22,
			20, 22, 23
		};
		unsigned int* indices = new unsigned int[sizeof(temp) / sizeof(unsigned int)];
		memcpy(indices, temp, sizeof(temp));
		set_elements(indices, sizeof(temp) / sizeof(unsigned int));
		set_draw_array(false);
	}

	cube::~cube()
	{

	}
	

	int cube::gen_vertex_data(float** data)
	{
		//(-width/2, width/2, -width/2)
		float px1 = -m_width / 2.0f;
		float py1 = m_width / 2.0f;
		float pz1 = -m_width / 2.0f;

		//(-widht/2, width/2, width/2)
		float px2 = -m_width / 2.0f;
		float py2 = m_width / 2.0f;
		float pz2 = m_width / 2.0f;

		//(width/2, width/2, width/2)
		float px3 = m_width / 2.0f;
		float py3 = m_width / 2.0f;
		float pz3 = m_width / 2.0f;


		//(width/2, width/2, -width/2)
		float px4 = m_width / 2.0f;
		float py4 = m_width / 2.0f;
		float pz4 = -m_width / 2.0f;

		//(-width/2, -width/2, -width/2)
		float px5 = -m_width / 2.0f;
		float py5 = -m_width / 2.0f;
		float pz5 = -m_width / 2.0f;

		//(-width/2, -width/2, width/2)
		float px6 = -m_width / 2.0f;
		float py6 = -m_width / 2.0f;
		float pz6 = m_width / 2.0f;

		//(width/2, -width/2, width/2)
		float px7 = m_width / 2.0f;
		float py7 = -m_width / 2.0f;
		float pz7 = m_width / 2.0f;

		//(width/2, -width/2, -width/2)
		float px8 = m_width / 2.0f;
		float py8 = -m_width / 2.0f;
		float pz8 = -m_width / 2.0f;

		float vertices[] = {
			px1, py1, pz1,
			px2, py2, pz2,
			px3, py3, pz3,
			px4, py4, pz4,

			px2, py2, pz2,
			px6, py6, pz6,
			px7, py7, pz7,
			px3, py3, pz3,

			px8, py8, pz8,
			px7, py7, pz7,
			px6, py6, pz6,
			px5, py5, pz5,

			px1, py1, pz1, 
			px4, py4, pz4, 
			px8, py8, pz8, 
			px5, py5, pz5, 

			px1, py1, pz1, 
			px5, py5, pz5, 
			px6, py6, pz6, 
			px2, py2, pz2,


			px4, py4, pz4,
			px3, py3, pz3,
			px7, py7, pz7,
			px8, py8, pz8,
		};
		*data = new float[sizeof(vertices) / sizeof(float)];
		memcpy(*data, vertices, sizeof(vertices));
		return sizeof(vertices);// / sizeof(float);
	}

	int cube::gen_texture_coord_data(float** data)
	{
		float vertices[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,

			1.0, 1.0,
			1.0, 0.0,
			0.0, 0.0,
			0.0f, 1.0,

			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0, 1.0,
			1.0f, 1.0f,

			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0, 1.0,
			1.0f, 0.0f,


			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0, 1.0,
			1.0, 1.0
		};
		*data = new float[sizeof(vertices) / sizeof(float)];
		memcpy(*data, vertices, sizeof(vertices));
		return sizeof(vertices);// / sizeof(float);
	}

}


