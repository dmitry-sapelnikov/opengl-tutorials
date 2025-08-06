// Includes
#include "RendererOpenGL.h"

#include <iostream>
#undef APIENTRY
#include <Windows.h>
#include <glad/glad.h>

#include "engine/core/Check.h"
#include "MeshOpenGL.h"
#include "ShaderOpenGL.h"
#include "TextureOpenGL.h"
#include "FramebufferOpenGL.h"

#include "../../../core/File.h"

namespace gltut
{

// Define the function pointer type
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);


// Global classes
RendererOpenGL::RendererOpenGL(Window& window) :
	RendererBase(window)
{
	GLTUT_CHECK(window.getDeviceContext() != nullptr, "Device context is null")

	HDC hdc = static_cast<HDC>(window.getDeviceContext());

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

void RendererOpenGL::clear(const Color& color) noexcept
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOpenGL::enableVSync(bool vSync) noexcept
{
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
		(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT != nullptr)
	{
		wglSwapIntervalEXT(vSync ? 1 : 0);
	}
	else
	{
		std::cerr << "wglSwapIntervalEXT is not supported, VSync cannot be enabled." << std::endl;
	}
}

void RendererOpenGL::setFramebuffer(Framebuffer* frameBuffer) noexcept
{
	if (frameBuffer == nullptr)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		frameBuffer->activate();
	}
}

void RendererOpenGL::setViewport(const Rectangle2u& viewport) noexcept
{
	const auto& min = viewport.getMin();
	const auto& max = viewport.getMax();
	glViewport(
		static_cast<GLint>(min.x),
		static_cast<GLint>(min.y),
		static_cast<GLsizei>(max.x - min.x),
		static_cast<GLsizei>(max.y - min.y));
}

std::unique_ptr<Mesh> RendererOpenGL::createBackendMesh(
	VertexFormat vertexFormat,
	u32 vertexCount,
	const float* vertices,
	u32 indexCount,
	const u32* indices)
{
	return std::make_unique<MeshOpenGL>(
		vertexFormat,
		vertexCount,
		vertices,
		indexCount,
		indices);
}

std::unique_ptr<Shader> RendererOpenGL::createBackendShader(
	const char* vertexShader,
	const char* fragmentShader)
{
	return std::make_unique<ShaderOpenGL>(*this, vertexShader, fragmentShader);
}

std::unique_ptr<Texture> RendererOpenGL::createBackendTexture(
	const void* data,
	u32 width,
	u32 height,
	Texture::Format format,
	Texture::FilterMode minFilter,
	Texture::FilterMode magFilter,
	Texture::WrapMode wrapMode)
{
	return std::make_unique<TextureOpenGL>(
		data,
		width,
		height,
		format,
		minFilter,
		magFilter,
		wrapMode);
}

std::unique_ptr<Framebuffer> RendererOpenGL::createBackendFramebuffer(
	Texture* color,
	Texture* depth)
{
	return std::make_unique<FramebufferOpenGL>(color, depth);
}

void RendererOpenGL::bindTexture(Texture* texture, u32 slot) noexcept
{
	if (slot >= Texture::TEXTURE_SLOTS)
	{
		return;
	}

	glActiveTexture(GL_TEXTURE0 + slot);
	if (texture == nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		texture->bind(slot);
	}
}

// End of the namespace gltut
}
