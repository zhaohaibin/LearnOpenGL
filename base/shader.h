#ifndef _shader_h
#define _shader_h
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <string>
using namespace std;

namespace gl
{
	class shader
	{
	public:
		shader(const string& vertex_shader_file, const string& fragment_shader_file);
		shader(const string& vertex_shader_file, const string& geometry_shader_file, const string& fragment_shader_file);
		~shader();

		bool initialize(string& error);
		void use();
		void un_use();
		void set_int(const string& name, int value);
		void set_float(const string& name, float value);
		void set_matrix4(const string& name, const glm::mat4& mat4);
		void set_vec3f(const std::string& name, const glm::vec3& vec);

		GLint get_attrib_location(const string& name);
	private:
		string load_file(const string& file_name);
		unsigned int create_shader(int gl_shader_type, const string& source, string& error);
		unsigned int build_shader_program(unsigned int vertex_shader_id, 
			unsigned int fragment_shader_id, string& error);
		unsigned int build_shader_program(unsigned int vertex_shader_id,
			unsigned int geometry_shader_id,
			unsigned int fragment_shader_id, string& error);
	private:
		string m_vertex_shader_file;
		string m_geometry_shader_file;
		string m_fragment_shader_file;
		unsigned int m_id;
	};
}
#endif //_shader_h
