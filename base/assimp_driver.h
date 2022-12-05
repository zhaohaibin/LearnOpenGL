#ifndef _ASSIMP_DRIVER_H
#define _ASSIMP_DRIVER_H
#include <vector>
#include <string>
#include "../base/mesh_node.h"
class node;
struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
namespace driver
{
	class assimp_driver
	{
	public:
		assimp_driver();
		node* read_file(const std::string& file);

	private:
		node* do_load_file(const std::string& file);
		node* process_node(aiNode* _aiNode, const aiScene* _aiScene);
		node* process_mesh(aiMesh* _aiMesh, const aiScene* _aiScene);
		node* create_node(mesh* _mesh);
		void do_get_texture(std::vector<texture>& textures, aiMaterial *mat, int type, const std::string& typeName);
		bool find_texture(const std::string& path, texture& _texture);
	private:
		std::string m_path;
		std::vector<texture> m_textures;
	};

	class test
	{
	public:
		test();
	};
}
#endif //_ASSIMP_DRIVER_H
