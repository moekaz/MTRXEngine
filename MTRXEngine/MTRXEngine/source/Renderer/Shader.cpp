#include <PrecompiledHeader.h>
#include "Shader.h"

Shader::Shader(const char* vertPath, const char* fragPath)
	: vertPath(vertPath), fragPath(fragPath)
{
	shaderID = load();
}

Shader::~Shader()
{
	glDeleteProgram(shaderID);
}

unsigned int Shader::load()
{
	// Create the program and shaders
	unsigned int program = glCreateProgram();
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// Variables need to be declared or the character pointers will become dangling pointers
	std::string vertSourceString = readFile(vertPath);
	std::string fragSourceString = readFile(fragPath);
	if (vertSourceString.empty() || fragSourceString.empty())
	{
		MTRX_ERROR("Vertex or Fragment shader is empty - failed to compile");
		return -1;
	}
	const char *vertSource = vertSourceString.c_str();
	const char *fragSource = fragSourceString.c_str();

	// Vertex Shader
	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);
	int result;

	// Check to see if it was successful
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		MTRX_ERROR("Failed to compile vertex shader");
		glDeleteShader(vertex);
		return 0;
	}

	//Fragment Shader
	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);

	// Check to see if it was successful
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		MTRX_ERROR("Failed to compile fragment shader");
		glDeleteShader(fragment);
		return 0;
	}

	// Attach the shaders to the program and link them
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glValidateProgram(program);

	// Delete the vertex and fragment shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	// Return the program id
	return program;
}

std::string Shader::readFile(const char* fileToRead)
{
	std::ifstream ifs(fileToRead);
	std::string result((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	return result;
}

int Shader::getUniformLocation(const char* name)
{
	return glGetUniformLocation(shaderID, name);
}

void Shader::setUniform1f(const char* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1i(const char* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform2f(const char* name, const glm::vec2& vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void Shader::setUniform3f(const char* name, const glm::vec3& vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(const char* name, const glm::vec4& vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniform4i(const char* name, const glm::ivec4& vector)
{
	glUniform4i(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformMat3(const char* name, const glm::mat3& matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformMat4(const char* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::enable() const
{
	glUseProgram(shaderID);
}

void Shader::disable() const
{
	glUseProgram(0);
}
