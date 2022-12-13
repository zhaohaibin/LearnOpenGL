#ifndef _NORMAL_TEXTURE_NODE_H
#define _NORMAL_TEXTURE_NODE_H

#include "../base/node.h"
class normal_texture_node : public node
{
public:
	normal_texture_node();

private:
	node* create_node();
	node* create_node_2();
	void calculate_tbn(const glm::vec3& pos_1, const glm::vec3& pos_2, const glm::vec3& pos_3,
		const glm::vec2& uv_1, const glm::vec2& uv_2, const glm::vec2& uv_3,
		glm::vec3& tangent, glm::vec3& bitangent, glm::vec3& normal);
};
#endif //_NORMAL_TEXTURE_NODE_H
