#include "assimp_driver.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "node.h"
#include "mesh_node.h"
#include "texture_loader.h"
#include "assimp/material.h"
#include "geometry_node.h"
#include "glad/glad.h"

namespace driver
{

	assimp_driver::assimp_driver()
	{

	}

	node* assimp_driver::read_file(const std::string& file)
	{
		m_path = file.substr(0, file.rfind("/")+1);
		return do_load_file(file);
	}

	node* assimp_driver::do_load_file(const std::string& file)
	{
		Assimp::Importer importer;
		/*
		aiProcess_Triangulate 告诉Assimp如果模型不是（全部）由三角形组成，它需要将模型所有图元形状变换为三角形
		aiProcess_FlipUVs 处理纹理坐标时翻转y轴纹理坐标。
		aiProcess_GenNormals 如果模型不包含法向量就为每个顶点创建法向量
		aiProcess_SpliteLargeMeshes 将比较大的网格分割成更小的网格，如果你的渲染有最大顶点数限制，只能渲染较小的网格，它非常有用
		aiProcess_OptimizeMeshes 将多个小网格拼接为一个大网格，减少绘制调用进行优化
		*/
		const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
		{
			importer.FreeScene();
			return nullptr;
		}

		node* _node = process_node(scene->mRootNode, scene);
		return _node;
	}

	node* assimp_driver::process_node(aiNode* _aiNode, const aiScene* _aiScene)
	{
		//解析_aiNode 构建 _node
		node* root = new node;
		for (int meshIndex = 0; meshIndex < _aiNode->mNumMeshes; ++meshIndex)
		{
			aiMesh* _mesh = _aiScene->mMeshes[_aiNode->mMeshes[meshIndex]];
			node* _node = process_mesh(_mesh, _aiScene);
			root->add_child(_node);
		}

		for (int i = 0; i < _aiNode->mNumChildren; ++i)
		{
			node* childe_node = process_node(_aiNode->mChildren[i], _aiScene);
			root->add_child(childe_node);
		}

		return root;
	}

	node* assimp_driver::process_mesh(aiMesh* _aiMesh, const aiScene* _aiScene)
	{
		mesh* _mesh = new mesh;
		_mesh->m_vertex_numbers = _aiMesh->mNumVertices;
		_mesh->m_vertex = new float[_aiMesh->mNumVertices * 3];
		memcpy(_mesh->m_vertex, _aiMesh->mVertices, sizeof(float) * 3 * _aiMesh->mNumVertices);

		if (_aiMesh->HasNormals())
		{
			_mesh->m_normal = new float[_aiMesh->mNumVertices * 3];
			memcpy(_mesh->m_normal, _aiMesh->mNormals, sizeof(float) * 3 * _aiMesh->mNumVertices);
		}

		if (_aiMesh->mTextureCoords[0])
		{
			_mesh->m_texcoords = new float[_aiMesh->mNumVertices * 3];
			memcpy(_mesh->m_texcoords, _aiMesh->mTextureCoords[0], sizeof(float) * 3 * _aiMesh->mNumVertices);

			if (_aiMesh->mTangents != nullptr)
			{
				_mesh->m_tangent = new float[_aiMesh->mNumVertices * 3];
				memcpy(_mesh->m_tangent, _aiMesh->mTangents, sizeof(float) * 3 * _aiMesh->mNumVertices);
			}

			if (_aiMesh->mBitangents != nullptr)
			{
				_mesh->m_bittangent = new float[_aiMesh->mNumVertices * 3];
				memcpy(_mesh->m_bittangent, _aiMesh->mBitangents, sizeof(float) * 3 * _aiMesh->mNumVertices);
			}
		}

		std::vector<unsigned int> index;
		for (unsigned int i = 0; i < _aiMesh->mNumFaces; i++)
		{
			aiFace face = _aiMesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				index.push_back(face.mIndices[j]);
		}
		if (index.size() > 0)
		{
			_mesh->m_index = new unsigned int[index.size()];
			_mesh->m_index_count = index.size();
			memcpy(_mesh->m_index, &index[0], sizeof(unsigned int)*index.size());
		}

		// process materials
		aiMaterial* material = _aiScene->mMaterials[_aiMesh->mMaterialIndex];
		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		// 1. diffuse maps
		do_get_texture(_mesh->m_textures, material, aiTextureType_DIFFUSE, "texture_diffuse");
		// 2. specular maps
		do_get_texture(_mesh->m_textures, material, aiTextureType_SPECULAR, "texture_specular");
		// 3. normal maps
		do_get_texture(_mesh->m_textures, material, aiTextureType_HEIGHT, "texture_normal");
		// 4. height maps
		do_get_texture(_mesh->m_textures, material, aiTextureType_AMBIENT, "texture_height");

		/*const aiMaterialProperty *const prop = material->mProperties[0];
		aiString s;
		aiGetMaterialString(material, prop->mKey.data, prop->mSemantic, prop->mIndex, &s);*/
		//return new mesh_node(_mesh);
		return create_node(_mesh);
	}

	node* assimp_driver::create_node(mesh* _mesh)
	{
		geometry_node* geo_node = new geometry_node;
		shader_file _shader_file;
		const string path = "D:/Workspace/opengl/WorkSpace/LearnOpenGL/base/";
		_shader_file.m_vertex_shader_file = path + "/shader/mesh_node/shader.vs";
		_shader_file.m_frag_shader_file = path + "/shader/mesh_node/shader.fs";
		geo_node->create_shader(_shader_file);
		geo_node->set_vertex(_mesh->m_vertex, _mesh->m_vertex_numbers * sizeof(float) * 3, 0);
		if (_mesh->m_normal != nullptr)
		{
			geo_node->set_vertex_normal(_mesh->m_normal, _mesh->m_vertex_numbers * sizeof(float) * 3, 1);
		}
		if (_mesh->m_texcoords != nullptr)
		{
			geo_node->set_vertex_texture(_mesh->m_texcoords, _mesh->m_vertex_numbers * sizeof(float) * 3, 2, 3);
		}
		if (_mesh->m_tangent != nullptr)
		{
			
		}
		else if (_mesh->m_bittangent != nullptr)
		{

		}
		geo_node->set_elements(_mesh->m_index, _mesh->m_index_count);
		//设置纹理
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < _mesh->m_textures.size(); ++i)
		{
			texture _texture = _mesh->m_textures[i];
			int num = 0;
			if (_texture.m_type == "texture_diffuse")
				num = diffuseNr++;
			else if (_texture.m_type == "texture_specular")
				num = specularNr++;
			else if (_texture.m_type == "texture_normal")
				num = normalNr++;
			else if (_texture.m_type == "texture_height")
				num = heightNr++;
			string  name = _texture.m_type + "_" + std::to_string(num);
			// 			unsigned int id = _mesh->m_textures[i].m_id;
			// 			m_shader->set_int(name, i);
			geometry_node::material _material;
			_material.m_file = _mesh->m_textures[i].m_path;
			_material.m_name = name;
			_material.m_id = _mesh->m_textures[i].m_id;
			geo_node->add_material(_material);
		}
		geo_node->set_primitive(GL_TRIANGLES);
		geo_node->set_draw_array(false);
		return geo_node;
	}

	void assimp_driver::do_get_texture(std::vector<texture>& textures, aiMaterial *mat, int type, const std::string& typeName)
	{
		for (unsigned int i = 0; i < mat->GetTextureCount((aiTextureType)type); i++)
		{
			aiString str;
			mat->GetTexture((aiTextureType)type, i, &str);
			texture _texture;
			std::string texture_path = m_path + str.C_Str();
			if (find_texture(texture_path, _texture))
			{
				textures.push_back(_texture);
			}
			else
			{
				_texture.m_type = typeName;
				_texture.m_path = m_path + str.C_Str();
				_texture.m_id = gl::load_texture_2d(_texture.m_path);
				textures.push_back(_texture);
				m_textures.push_back(_texture);
			}
		}
	}

	bool assimp_driver::find_texture(const std::string& path, texture& _texture)
	{
		for (int i = 0; i < m_textures.size(); ++i)
		{
			if (m_textures[i].m_path == path)
			{
				_texture = m_textures[i];
				return true;
			}
		}
		return false;
	}

	test::test()
	{
		//assimp_driver obj_driver;
		//obj_driver.read_file("D:/Workspace/opengl/LearnOpenGL/resources/objects/backpack/backpack.obj");
	}

	test _test;
}


