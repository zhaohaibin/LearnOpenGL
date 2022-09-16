#include "shader.h"

#include <fstream>
#include <sstream>
namespace gl
{
	shader::shader(const string& vertex_shader_file, const string& fragment_shader_file)
		: m_vertex_shader_file(vertex_shader_file)
		, m_fragment_shader_file(fragment_shader_file)
		, m_id(0)
	{

	}

	shader::shader(const string& vertex_shader_file, 
		const string& geometry_shader_file, 
		const string& fragment_shader_file)
		: m_vertex_shader_file(vertex_shader_file)
		, m_geometry_shader_file(geometry_shader_file)
		, m_fragment_shader_file(fragment_shader_file)
		, m_id(0)
	{

	}

	shader::~shader()
	{
		if (m_id != 0)
		{
			glDeleteProgram(m_id);
			m_id = 0;
		}
	}

	bool shader::initialize(string& error)
	{
		string vertex_shader_source = load_file(m_vertex_shader_file);
		string fragment_shader_source = load_file(m_fragment_shader_file);

		unsigned int vertex_shader_id = create_shader(GL_VERTEX_SHADER, vertex_shader_source, error);
		if (0 == vertex_shader_id)
			return false;

		unsigned int geometry_shader_id = 0;
		if (m_geometry_shader_file.empty() == false)
		{
			string geometry_shader_source = load_file(m_geometry_shader_file);
			geometry_shader_id = create_shader(GL_GEOMETRY_SHADER, geometry_shader_source, error);
			if (0 == geometry_shader_id)
			{
				glDeleteShader(vertex_shader_id);
				return false;
			}
		}

		unsigned int fragment_shader_id = create_shader(GL_FRAGMENT_SHADER, fragment_shader_source, error);
		if (0 == fragment_shader_id)
		{
			glDeleteShader(vertex_shader_id);
			if (0 != geometry_shader_id)
				glDeleteShader(geometry_shader_id);
			return false;
		}

		if (geometry_shader_id == 0)
			m_id = build_shader_program(vertex_shader_id, fragment_shader_id, error);
		else
			m_id = build_shader_program(vertex_shader_id, geometry_shader_id, fragment_shader_id, error);

		glDeleteShader(vertex_shader_id);
		if (0 != geometry_shader_id)
			glDeleteShader(geometry_shader_id);
		glDeleteShader(fragment_shader_id);

		return 0 != m_id;
	}

	void shader::use()
	{
		glUseProgram(m_id);
	}

	void shader::un_use()
	{
		glUseProgram(0);
	}

	void shader::set_int(const string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
	}

	void shader::set_float(const string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
	}

	void shader::set_matrix4(const string& name, const glm::mat4& mat4)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
	}

	void shader::set_vec3f(const std::string& name, const glm::vec3& vec)
	{
		glUniform3f(glGetUniformLocation(m_id, name.c_str()), vec.r, vec.g, vec.b);
	}

	GLint shader::get_attrib_location(const string& name)
	{
		return glGetAttribLocation(m_id, name.c_str());
	}

	std::string shader::load_file(const string& file_name)
	{
		std::ifstream file_stream;
		file_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			file_stream.open(file_name);
			std::stringstream string_stream;
			string_stream << file_stream.rdbuf();
			return string_stream.str();
		}
		catch (const std::ifstream::failure& e)
		{
			return e.what();
		}
	}

	unsigned int shader::create_shader(int gl_shader_type, const string& source, string& error)
	{
		unsigned int id = glCreateShader(gl_shader_type);
		const char* p = source.c_str();
		glShaderSource(id, 1, &p, nullptr);
		glCompileShader(id);

		int success;
		char info_log[512];
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (0 != success)
			return id;

		glGetShaderInfoLog(id, 512, NULL, info_log);
		error.append(info_log);
		return 0;
	}

	unsigned int shader::build_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id, string& error)
	{
		unsigned int id = glCreateProgram();
		glAttachShader(id, vertex_shader_id);
		glAttachShader(id, fragment_shader_id);

		glLinkProgram(id);
		int success;
		char info_log[512];
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (0 != success)
			return id;
		glGetProgramInfoLog(id, 512, NULL, info_log);
		error.append(info_log);
		return 0;
	}

	unsigned int shader::build_shader_program(unsigned int vertex_shader_id, 
		unsigned int geometry_shader_id, 
		unsigned int fragment_shader_id, string& error)
	{
		unsigned int id = glCreateProgram();
		glAttachShader(id, vertex_shader_id);
		glAttachShader(id, geometry_shader_id);
		glAttachShader(id, fragment_shader_id);

		glLinkProgram(id);
		int success;
		char info_log[512];
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (0 != success)
			return id;
		glGetProgramInfoLog(id, 512, NULL, info_log);
		error.append(info_log);
		return 0;
	}

}


