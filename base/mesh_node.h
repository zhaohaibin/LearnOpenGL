#ifndef _MESH_NODE_H
#define _MESH_NODE_H
#include <string>
#include <vector>
#include "node.h"

struct texture
{
	std::string m_type;
	std::string m_path;
	unsigned int m_id;
};

struct mesh
{
	mesh();
	int m_vertex_numbers;
	float* m_vertex;
	float* m_normal;
	float* m_texcoords;
	float* m_tangent;
	float* m_bittangent;

	unsigned int* m_index;
	unsigned int m_index_count;
	std::vector<texture> m_textures;
};

class mesh_node : public node
{
public:
	mesh_node(mesh* _mesh);

protected:
	virtual bool initialize();
	virtual void drawing();
private:
	mesh* m_mesh;
};
#endif //_MESH_NODE_H
