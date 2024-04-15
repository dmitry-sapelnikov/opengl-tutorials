// Includes
#include "framework/shaders.h"
#include <iostream>

namespace gltut
{
// Local constants
namespace
{
	const size_t BUFFER_SIZE = 512;
}

// Global functions
unsigned createShader(GLenum shaderType, const char* shaderSource)
{
	//	Create the shader
	unsigned shader = glCreateShader(shaderType);
	if (!shader)
	{
		std::cerr << "ERROR::SHADER::CREATION_FAILED\n";
		return 0;
	}

	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	//	Check for shader compilation errors
	int shaderCompilationSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess)
	{
		char infoLog[BUFFER_SIZE];
		glGetShaderInfoLog(shader, BUFFER_SIZE, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	return shader;
}

unsigned createShaderProgram(
	const char* vertexShaderSource,
	const char* fragmentShaderSource)
{
	unsigned vertexShader = createShader(
		GL_VERTEX_SHADER,
		vertexShaderSource);

	if (!vertexShader)
	{
		return 0;
	}

	unsigned fragmentShader = createShader(
		GL_FRAGMENT_SHADER,
		fragmentShaderSource);

	if (!fragmentShader)
	{
		return 0;
	}

	//	Create the shader program
	unsigned shaderProgram = glCreateProgram();
	if (!shaderProgram)
	{
		std::cerr << "ERROR::SHADER_PROGRAM::CREATION_FAILED\n";
		return 0;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//	Check for shader program linking errors
	int shaderProgramLinkingSuccess;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramLinkingSuccess);
	if (!shaderProgramLinkingSuccess)
	{
		char infoLog[BUFFER_SIZE];
		glGetProgramInfoLog(shaderProgram, BUFFER_SIZE, nullptr, infoLog);
		std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

// End of the namespace gltut
}
