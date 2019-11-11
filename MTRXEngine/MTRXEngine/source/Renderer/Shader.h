/*
	Author: Brady Jessup
	Description: Class the handles an OpenGL program and passing data to the program on the GPU
*/

#pragma once

#include <log/LogManager.h>
#include <Defs.h>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const char* vertPath, const char* fragPath);
	~Shader();

	void enable() const;
	void disable() const;

	void setUniform1f(const char* name, float value);
	void setUniform1i(const char* name, int value);
	void setUniform2f(const char* name, const glm::vec2& vector);
	void setUniform3f(const char* name, const glm::vec3& vector);
	void setUniform4f(const char* name, const glm::vec4& vector);
	void setUniform4i(const char* name, const glm::ivec4& vector);
	void setUniformMat3(const char* name, const glm::mat3& matrix);
	void setUniformMat4(const char* name, const glm::mat4& matrix);

private:
	int getUniformLocation(const char* name);

	unsigned int load();
	std::string readFile(const char* fileToRead);
private:
	unsigned int shaderID;
	const char *vertPath, *fragPath;
};
