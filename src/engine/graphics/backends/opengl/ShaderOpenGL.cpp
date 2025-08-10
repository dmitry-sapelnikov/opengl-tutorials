// Includes
#include "ShaderOpenGL.h"

#include <iostream>
#include <glad/glad.h>
#include "engine/core/Check.h"

namespace gltut
{
// Local constants
namespace
{
	const size_t BUFFER_SIZE = 512;
}

static_assert(sizeof(GLuint) == sizeof(u32), "GLuint must be the same size as u32");

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
	const std::string& fragmentCode) :

	mProgram(0)
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

void ShaderOpenGL::bind() const noexcept
{
	glUseProgram(mProgram);
}

int32 ShaderOpenGL::getParameterLocation(const char* name) const noexcept
{
	GLTUT_ASSERT_STRING(name);
	bind();
	return glGetUniformLocation(mProgram, name);
}

void ShaderOpenGL::setInt(int32 location, int value) noexcept
{
	bind();
	glUniform1i(location, value);
}

void ShaderOpenGL::setFloat(int32 location, float value) noexcept
{
	bind();
	glUniform1f(location, value);
}

void ShaderOpenGL::setVec2(int32 location, float x, float y) noexcept
{
	bind();
	glUniform2f(location, x, y);
}

void ShaderOpenGL::setVec3(int32 location, float x, float y, float z) noexcept
{
	bind();
	glUniform3f(location, x, y, z);
}

void ShaderOpenGL::setVec4(int32 location, float x, float y, float z, float w) noexcept
{
	bind();
	glUniform4f(location, x, y, z, w);
}

void ShaderOpenGL::setMat3(int32 location, const float* data) noexcept
{
	bind();
	glUniformMatrix3fv(location, 1, GL_FALSE, data);
}

void ShaderOpenGL::setMat4(int32 location, const float* data) noexcept
{
	bind();
	glUniformMatrix4fv(location, 1, GL_FALSE, data);
}


// End of the namespace gltut
}
