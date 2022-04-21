#pragma once

#include <GLEW/glew.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>


class UniformManager
{
public:
	~UniformManager();
	static std::shared_ptr<UniformManager>& get();

	UniformManager& operator=(const UniformManager&) = delete;
	UniformManager(const UniformManager&) = delete;

private:
	UniformManager() {}

	static std::shared_ptr<UniformManager> x_instance;
	unsigned int x_getUniformLocation(const std::string& uniform_name, unsigned int shader_program_id);

private:
	std::unordered_map<unsigned int, std::unordered_map<std::string, unsigned int>> x_shader_uniforms_cache;

public:
	void setUniform(const std::string& name, unsigned int shader_program_id, int v0);
	void setUniform(const std::string& name, unsigned int shader_program_id, float v0);
	void setUniform(const std::string& name, unsigned int shader_program_id, float v0, float v1, float v2);
	void setUniform(const std::string& name, unsigned int shader_program_id, float v0, float v1, float v2, float v3);
	void setUniformVec3(const std::string& name, unsigned int shader_program_id, const float* value);
	void setUniformMatrix4fv(const std::string& name, unsigned int shader_program_id, const float* value);
};