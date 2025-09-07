// Includes
#include "ShaderUniformBufferOpenGL.h"

#include <iostream>
#include <glad/glad.h>
#include "engine/core/Check.h"

namespace gltut
{

static_assert(sizeof(GLuint) == sizeof(u32), "GLuint must be the same size as u32");

ShaderUniformBufferOpenGL::ShaderUniformBufferOpenGL(u32 sizeInBytes) :
	mSizeInBytes(sizeInBytes),
	mId(0)
{
	GLTUT_CHECK(sizeInBytes > 0, "Size in bytes must be greater than 0");

	glGenBuffers(1, &mId);
	GLTUT_CHECK(mId != 0, "Failed to generate a uniform buffer");

	bind();
	glBufferData(GL_UNIFORM_BUFFER, static_cast<GLsizeiptr>(sizeInBytes), nullptr, GL_DYNAMIC_DRAW);
}

ShaderUniformBufferOpenGL::~ShaderUniformBufferOpenGL() noexcept
{
	if (mId != 0)
	{
		glDeleteBuffers(1, &mId);
	}
}

void ShaderUniformBufferOpenGL::setData(const void* data, u32 size, u32 offset) noexcept
{
	if (GLTUT_ASSERT(data != nullptr) &&
		GLTUT_ASSERT(size > 0) &&
		GLTUT_ASSERT(offset + size <= mSizeInBytes))
	{
		bind();
		glBufferSubData(
			GL_UNIFORM_BUFFER,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size),
			data);
	}
}

void ShaderUniformBufferOpenGL::bind() const noexcept
{
	glBindBuffer(GL_UNIFORM_BUFFER, mId);
}

// End of the namespace gltut
}
