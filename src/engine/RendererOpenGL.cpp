// Includes
#include "RendererOpenGL.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/core/Check.h"
#include "engine/VertexFormat.h"
#include "ShaderOpenGL.h"
#include "File.h"

namespace gltut
{
// Global classes
RendererOpenGL::RendererOpenGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}

	//	Check that the current shader program is 0
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
	GLTUT_ASSERT(currentProgram == 0);
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

void RendererOpenGL::freeBuffer(unsigned buffer) noexcept
{
	glDeleteBuffers(1, &buffer);
}

u32 RendererOpenGL::allocateVertexArray(
	VertexFormat vertexFormat,
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

Shader* RendererOpenGL::createShader(
	const char* vertexShader,
	const char* fragmentShader) noexcept
{
	try
	{
		mShaders.emplace_back(
			std::make_unique<ShaderOpenGL>(vertexShader, fragmentShader));
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
	return mShaders.back().get();
}

Shader* RendererOpenGL::loadShader(
	const char* vertexShaderPath,
	const char* fragmentShaderPath) noexcept
{
	try
	{
		const auto vertexSource = readFileToString(vertexShaderPath);
		const auto fragmentSource = readFileToString(fragmentShaderPath);
		return createShader(
			vertexSource.c_str(),
			fragmentSource.c_str());
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

void RendererOpenGL::removeShader(Shader* shader) noexcept
{
	if (shader == nullptr)
	{
		return;
	}

	auto findResult = std::find_if(
		mShaders.begin(),
		mShaders.end(),
		[&shader](const auto& s)
		{
			return s.get() == shader;
		});

	if (findResult != mShaders.end())
	{
		mShaders.erase(findResult);
	}
	else
	{
		std::cerr << "Failed to remove the shader" << std::endl;
	}
}

// End of the namespace gltut
}
