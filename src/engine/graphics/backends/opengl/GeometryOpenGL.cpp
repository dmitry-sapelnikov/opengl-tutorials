// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "GeometryOpenGL.h"

#include "engine/core/Check.h"
#include <glad/glad.h>

namespace gltut
{

namespace
{
// Local functions
static_assert(sizeof(GLuint) == sizeof(u32), "GLuint must be the same size as u32");

GLuint allocateVertexBuffer(const float* vertices, u32 count) noexcept
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	GLTUT_ASSERT(vbo != 0);

	// Get the currently bound buffer to restore it later
	GLint currentBuffer = 0;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Restore the previously bound buffer
	glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(currentBuffer));
	return vbo;
}

GLuint allocateIndexBuffer(const u32* indices, u32 count) noexcept
{
	GLuint ibo = 0;
	glGenBuffers(1, &ibo);
	GLTUT_ASSERT(ibo != 0);

	// Get the currently bound buffer to restore it later
	GLint currentBuffer = 0;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * count, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Restore the previously bound buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(currentBuffer));

	return ibo;
}

GLuint allocateVertexArray(
	VertexFormat vertexFormat,
	GLuint vertexBuffer,
	GLuint indexBuffer) noexcept
{
	GLTUT_ASSERT(vertexBuffer != 0);
	GLTUT_ASSERT(indexBuffer != 0);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	GLTUT_ASSERT(vao != 0);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	const u32 stride = vertexFormat.getTotalSizeInBytes();
	size_t offset = 0;
	for (u32 i = 0; i < VertexFormat::MAX_VERTEX_COMPONENTS; ++i)
	{
		if (vertexFormat.getComponentSize(i) == 0)
		{
			break;
		}

		glVertexAttribPointer(
			i,
			vertexFormat.getComponentSize(i),
			GL_FLOAT,
			GL_FALSE,
			stride,
			reinterpret_cast<const void*>(offset));

		glEnableVertexAttribArray(i);

		offset += vertexFormat.getComponentSizeInBytes(i);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return vao;
}

// End of the anonymous namespace
}

// Global classes
GeometryOpenGL::GeometryOpenGL(
	VertexFormat vertexFormat,
	u32 vertexCount,
	const float* vertices,
	u32 indexCount,
	const u32* indices) :

	mIndexCount(indexCount)
{
	GLTUT_CHECK(vertexCount > 0, "Vertex count must be greater than 0");
	GLTUT_CHECK(vertices != nullptr, "Vertex data must not be null");

	GLTUT_CHECK(indexCount > 0, "Index count must be greater than 0");
	GLTUT_CHECK(indexCount % 3 == 0, "Index count must be a multiple of 3");
	GLTUT_CHECK(indices != nullptr, "Index data must not be null");

	mVertexBuffer = allocateVertexBuffer(vertices, vertexCount * vertexFormat.getTotalSize());
	mIndexBuffer = allocateIndexBuffer(indices, indexCount);
	mVertexArray = allocateVertexArray(vertexFormat, mVertexBuffer, mIndexBuffer);
}

GeometryOpenGL::~GeometryOpenGL()
{
	glDeleteVertexArrays(1, &mVertexArray);
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
}

void GeometryOpenGL::render() const noexcept
{
	glBindVertexArray(mVertexArray);
	glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, nullptr);
}

// End of the namespace gltut
}
