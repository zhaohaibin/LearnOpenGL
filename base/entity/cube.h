#ifndef _ENTITY_CUBE_H
#define _ENTITY_CUBE_H

#include "../geometry_node.h"
#include <glm/glm.hpp>

namespace entity
{
	class cube : public geometry_node
	{
	public:
		cube(float width, const string& texture_image, glm::mat4 model_matrix = glm::mat4(1.0f));
		~cube();

	private:
		int gen_vertex_data(float** data);
		int gen_texture_coord_data(float** data);
	private:
		float m_width;
		string m_texture_image;
		bool m_init;
		unsigned int* m_indices;
		unsigned int m_texture;
		gl::shader* m_shader;
	};
}


#endif //_CUBE_H
