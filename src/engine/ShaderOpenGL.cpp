// Includes
#include "ShaderOpenGL.h"
#include "engine/core/Check.h"
#include <iostream>
#include <glad/glad.h>

namespace gltut
{
// Local constants
namespace
{
	const size_t BUFFER_SIZE = 512;
}

// Local functions
unsigned createShader(
	GLenum shaderType,
	const std::string& shaderSource)
{
	GLTUT_CHECK(!shaderSource.empty(), "Shader source is empty");

	//	Create the shader
	unsigned shader = glCreateShader(shaderType);
	GLTUT_CHECK(shader != 0, "Failed to create shader");

	const char* charPointer = shaderSource.c_str();
	glShaderSource(shader, 1, &charPointer, nullptr);
	glCompileShader(shader);

	//	Check for shader compilation errors
	int shaderCompilationSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess)
	{
		char infoLog[BUFFER_SIZE];
		glGetShaderInfoLog(shader, BUFFER_SIZE, nullptr, infoLog);
		throw std::runtime_error("Shader compilation failed:\n" + std::string(infoLog));
	}
	return shader;
}

ShaderOpenGL::ShaderOpenGL(
	const std::string& vertexCode,
	const std::string& fragmentCode)
{
	unsigned vertexShader = createShader(
		GL_VERTEX_SHADER,
		vertexCode);

	unsigned fragmentShader = createShader(
		GL_FRAGMENT_SHADER,
		fragmentCode);

	//	Create the shader program
	mProgram = glCreateProgram();
	GLTUT_CHECK(mProgram != 0, "Failed to create shader program");

	glAttachShader(mProgram, vertexShader);
	glAttachShader(mProgram, fragmentShader);
	glLinkProgram(mProgram);

	//	Check for shader program linking errors
	int shaderProgramLinkingSuccess;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &shaderProgramLinkingSuccess);
	if (!shaderProgramLinkingSuccess)
	{
		char infoLog[BUFFER_SIZE];
		glGetProgramInfoLog(mProgram, BUFFER_SIZE, nullptr, infoLog);
		throw std::runtime_error("Shader program linking failed:\n" + std::string(infoLog));
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

ShaderOpenGL::~ShaderOpenGL() noexcept
{
	glDeleteProgram(mProgram);
}

void ShaderOpenGL::use() noexcept
{
	glUseProgram(mProgram);
}

void ShaderOpenGL::setBool(const char* name, bool value) noexcept
{
	GLTUT_ASSERT_STRING(name);
	glUniform1i(glGetUniformLocation(mProgram, name), static_cast<int>(value));
}

void ShaderOpenGL::setInt(const char* name, int value) noexcept
{
	GLTUT_ASSERT_STRING(name);
	glUniform1i(glGetUniformLocation(mProgram, name), value);
}

void ShaderOpenGL::setFloat(const char* name, float value) noexcept
{
	GLTUT_ASSERT_STRING(name);
	glUniform1f(glGetUniformLocation(mProgram, name), value);
}

void ShaderOpenGL::setVec2(const char* name, float x, float y) noexcept
{
	GLTUT_ASSERT_STRING(name);
	glUniform2f(glGetUniformLocation(mProgram, name), x, y);
}

void ShaderOpenGL::setVec3(const char* name, float x, float y, float z) noexcept
{
	GLTUT_ASSERT_STRING(name);
	glUniform3f(glGetUniformLocation(mProgram, name), x, y, z);
}

void ShaderOpenGL::setVec4(const char* name, float x, float y, float z, float w) noexcept
{
	GLTUT_ASSERT_STRING(name);
	glUniform4f(glGetUniformLocation(mProgram, name), x, y, z, w);
}

// End of the namespace gltut
}
