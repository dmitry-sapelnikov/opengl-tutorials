// Includes
#include "RendererOpenGL.h"

#include <iostream>
#undef APIENTRY
#include <Windows.h>

#include "engine/core/Check.h"
#include "engine/VertexFormat.h"
#include "ShaderOpenGL.h"
#include "TextureOpenGL.h"
#include "stb_image.h"
#include "File.h"

namespace gltut
{

// Define the function pointer type
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);

// Local functions
template <typename T>
void removeElement(
	std::vector<std::unique_ptr<T>>& container,
	T* element,
	const char* elementName)
{
	if (element == nullptr)
	{
		return;
	}

	auto findResult = std::find_if(
		container.begin(),
		container.end(),
		[&element](const auto& e)
		{
			return e.get() == element;
		});

	if (findResult != container.end())
	{
		container.erase(findResult);
	}
	else
	{
		std::cerr << "Failed to remove the element: " << elementName << std::endl;
	}
}

// Global classes
RendererOpenGL::RendererOpenGL(void* deviceContext) :
	mDeviceContext(deviceContext)
{
	GLTUT_CHECK(mDeviceContext != nullptr, "Device context is null")

	HDC hdc = static_cast<HDC>(mDeviceContext);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	
	GLTUT_CHECK(SetPixelFormat(hdc, pixelFormat, &pfd), "Failed to set the pixel format");

	HGLRC hglrc = wglCreateContext(hdc);
	GLTUT_CHECK(hglrc != nullptr, "Failed to create the OpenGL context");
	GLTUT_CHECK(wglMakeCurrent(hdc, hglrc), "Failed to make the OpenGL context current");

	// Load GLAD
	if (!gladLoadGL())
	{
		GLTUT_CHECK(false, "Failed to load GLAD");
	}

	//	Check that the current shader program is 0
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
	GLTUT_ASSERT(currentProgram == 0);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Disable VSync
	enableVSync(false);
}

void RendererOpenGL::setClearColor(float r, float g, float b, float a) noexcept
{
	glClearColor(r, g, b, a);
}

void RendererOpenGL::clear() noexcept
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

u32 RendererOpenGL::addMesh(const Mesh& mesh) noexcept
{
	const auto& vertexFormat = mesh.getVertexFormat();

	const u32 vbo = allocateVertexBuffer(
		mesh.getVertices(),
		mesh.getVertexCount() * vertexFormat.getTotalSize());

	const u32 ibo = allocateIndexBuffer(
		mesh.getIndices(),
		mesh.getIndexCount());

	const u32 vao = allocateVertexArray(
		vertexFormat,
		vbo,
		ibo);

	GLTUT_CATCH_ALL_BEGIN
	if (mFreeMeshIndices.empty())
	{
		mMeshBuffers.emplace_back(vbo, ibo, mesh.getIndexCount(), vao);
		return static_cast<u32>(mMeshBuffers.size() - 1);
	}
	else
	{
		const u32 index = mFreeMeshIndices.back();
		mFreeMeshIndices.pop_back();
		mMeshBuffers[index] = { vbo, ibo, mesh.getIndexCount(), vao };
		return index;
	}
	GLTUT_CATCH_ALL_END("Failed to add mesh")

	return INVALID_MESH_INDEX;
}

void RendererOpenGL::removeMesh(u32 index) noexcept
{
	GLTUT_ASSERT(index < mMeshBuffers.size());

	auto& buffer = mMeshBuffers[index];
	GLTUT_ASSERT(buffer.isValid());

	glDeleteVertexArrays(1, &buffer.vao);
	glDeleteBuffers(1, &buffer.vertexBuffer);
	glDeleteBuffers(1, &buffer.indexBuffer);

	//	Reset the buffer to prevent accidental further use
	buffer.reset();

	GLTUT_CATCH_ALL_BEGIN
		mFreeMeshIndices.emplace_back(index);
	GLTUT_CATCH_ALL_END("Failed to remove mesh")
}

void RendererOpenGL::renderMesh(u32 index) const noexcept
{
	GLTUT_ASSERT(index < mMeshBuffers.size());

	const auto& buffer = mMeshBuffers[index];
	GLTUT_ASSERT(buffer.isValid());

	glBindVertexArray(buffer.vao);
	glDrawElements(GL_TRIANGLES, buffer.indicesCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

GLuint RendererOpenGL::allocateVertexBuffer(float* vertices, u32 count) noexcept
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	GLTUT_ASSERT(vbo != 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

GLuint RendererOpenGL::allocateIndexBuffer(u32* indices, u32 count) noexcept
{
	GLuint ibo = 0;
	glGenBuffers(1, &ibo);
	GLTUT_ASSERT(ibo != 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * count, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return ibo;
}

GLuint RendererOpenGL::allocateVertexArray(
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
	removeElement(mShaders, shader, "Shader");
}

Texture* RendererOpenGL::createTexture(
	const u8* data,
	u32 width,
	u32 height,
	u32 channels) noexcept
{
	try
	{
		mTextures.emplace_back(std::make_unique<TextureOpenGL>(
			data,
			width,
			height,
			channels));
		return mTextures.back().get();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

void RendererOpenGL::removeTexture(Texture* texture) noexcept
{
	removeElement(mTextures, texture, "Texture");
}

void RendererOpenGL::onResize(u32 width, u32 height) noexcept
{
	glViewport(0, 0, width, height);
	RendererBase::onResize(width, height);
}

void RendererOpenGL::enableVSync(bool vSync) noexcept
{
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
		(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	GLTUT_ASSERT(wglSwapIntervalEXT != nullptr);
	wglSwapIntervalEXT(vSync ? 1 : 0);
}

// End of the namespace gltut
}
