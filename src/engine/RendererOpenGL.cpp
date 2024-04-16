// Includes
#include "RendererOpenGL.h"

#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/core/Assert.h"
#include "Shaders.h"

namespace gltut
{
// Global classes
RendererOpenGL::RendererOpenGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}
}

void RendererOpenGL::setClearColor(float r, float g, float b, float a) noexcept
{
	glClearColor(r, g, b, a);
}

void RendererOpenGL::clear() noexcept
{
	glClear(GL_COLOR_BUFFER_BIT);
}

u32 RendererOpenGL::allocateVertexBuffer(float* vertices, u32 count) noexcept
{
	u32 vbo = 0;
	glGenBuffers(1, &vbo);
	GLTUT_ASSERT(vbo != 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

u32 RendererOpenGL::allocateIndexBuffer(u32* indices, u32 count) noexcept
{
	u32 ibo = 0;
	glGenBuffers(1, &ibo);
	GLTUT_ASSERT(ibo != 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * count, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return ibo;
}

void RendererOpenGL::freeBuffer(u32 buffer) noexcept
{
	glDeleteBuffers(1, &buffer);
}

u32 RendererOpenGL::allocateVertexArray(
	unsigned vertexBuffer,
	unsigned indexBuffer) noexcept
{
	GLTUT_ASSERT(vertexBuffer != 0);
	GLTUT_ASSERT(indexBuffer != 0);

	u32 vao = 0;
	glGenVertexArrays(1, &vao);
	GLTUT_ASSERT(vao != 0);

	glBindVertexArray(vao);
	setVertexBuffer(vertexBuffer);
	setIndexBuffer(indexBuffer);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		nullptr);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	setVertexBuffer(0);
	setIndexBuffer(0);
	return vao;
}

void RendererOpenGL::freeVertexArray(unsigned array) noexcept
{
	glDeleteVertexArrays(1, &array);
}

void RendererOpenGL::setVertexBuffer(unsigned buffer) noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void RendererOpenGL::setIndexBuffer(unsigned buffer) noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void RendererOpenGL::setVertexArray(unsigned array) noexcept
{
	glBindVertexArray(array);
}

void RendererOpenGL::drawIndexedTriangles(u32 indicesCount) noexcept
{
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
}

unsigned RendererOpenGL::createShaderProgram(
	const char* vertexShader,
	const char* fragmentShader) noexcept
{
	unsigned result = gltut::createShaderProgram(vertexShader, fragmentShader);
	GLTUT_ASSERT(result != 0);
	return result;
}

void RendererOpenGL::setShaderProgram(unsigned program) noexcept
{
	glUseProgram(program);
}

void RendererOpenGL::freeShaderProgram(unsigned program) noexcept
{
	glDeleteProgram(program);
}

// End of the namespace gltut
}
