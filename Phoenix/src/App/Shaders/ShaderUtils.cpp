#include "ShaderUtils.h"

unsigned int  ShaderUtils::buildShaderFromFile(const char* file_path, GLenum shader_type)
{
	std::ifstream shader_file;
	std::stringstream shader_code_stream;
	std::string shader_code_str;
	const char* shader_code;
	unsigned int shader_id;

	shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		shader_file.open(file_path);
		shader_code_stream << shader_file.rdbuf();
		shader_file.close();
		shader_code_str = shader_code_stream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}
	shader_code = shader_code_str.c_str();
	shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &shader_code, NULL);
	glCompileShader(shader_id);

	x_checkErrors(shader_id, CheckType::SHADER_IV);
	return shader_id;
}

unsigned int ShaderUtils::buildShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id)
{
	// shader Program
	unsigned int shader_program_id;
	shader_program_id = glCreateProgram();
	glAttachShader(shader_program_id, vertex_shader_id);
	glAttachShader(shader_program_id, fragment_shader_id);
	glLinkProgram(shader_program_id);

	//TODO:Cleanup
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	x_checkErrors(shader_program_id, CheckType::PROGRAM_IV);
	return shader_program_id;
}

void ShaderUtils::x_checkErrors(unsigned int id, CheckType type)
{
	int success;
	char info_log[1024];
	switch (type)
	{
	case CheckType::SHADER_IV: {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 1024, NULL, info_log);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
		}
		break;
	}
	case CheckType::PROGRAM_IV: {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 1024, NULL, info_log);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
		}
		break;
	}

	default:

		break;
	}
}
