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

int32 ShaderOpenGL::getVariableLocation(const char* name) noexcept
{
	GLTUT_ASSERT_STRING(name);
	use();
	return glGetUniformLocation(mProgram, name);
}

void ShaderOpenGL::setBool(const char* name, bool value) noexcept
{
	glUniform1i(getCheckedVariableLocation(name), static_cast<int>(value));
}

void ShaderOpenGL::setInt(const char* name, int value) noexcept
{
	glUniform1i(getCheckedVariableLocation(name), value);
}

void ShaderOpenGL::setFloat(const char* name, float value) noexcept
{
	glUniform1f(getCheckedVariableLocation(name), value);
}

void ShaderOpenGL::setVec2(const char* name, float x, float y) noexcept
{
	glUniform2f(getCheckedVariableLocation(name), x, y);
}

void ShaderOpenGL::setVec3(const char* name, float x, float y, float z) noexcept
{
	glUniform3f(getCheckedVariableLocation(name), x, y, z);
}

void ShaderOpenGL::setVec4(const char* name, float x, float y, float z, float w) noexcept
{
	glUniform4f(getCheckedVariableLocation(name), x, y, z, w);
}

void ShaderOpenGL::setMat4(const char* name, const float* data) noexcept
{
	glUniformMatrix4fv(getCheckedVariableLocation(name), 1, GL_FALSE, data);
}

int ShaderOpenGL::getCheckedVariableLocation(const char* name) noexcept
{
	const int location = getVariableLocation(name);
	GLTUT_ASSERT(location != -1);
	return location;
}

// End of the namespace gltut
}
