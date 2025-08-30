// Includes
#include "DeviceOpenGL.h"

#include <iostream>
#undef APIENTRY
#include <Windows.h>
#include <glad/glad.h>

#include "engine/core/Check.h"
#include "GeometryOpenGL.h"
#include "ShaderOpenGL.h"
#include "TextureOpenGL.h"

#include "../../../core/File.h"
#include "./framebuffer/TextureFramebufferOpenGL.h"

namespace gltut
{

// Define the function pointer type
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);


// Global classes
DeviceOpenGL::DeviceOpenGL(Window& window) :
	GraphicsDeviceBase(window),
	mWindowFramebuffer(std::make_unique<WindowFramebufferOpenGL>(window))
{
	GLTUT_CHECK(window.getDeviceContext() != nullptr, "Device context is null")

	HDC hdc = static_cast<HDC>(window.getDeviceContext());

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
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

	// Set default blend function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Disable VSync
	enableVSync(false);

	// Enable face culling
	glEnable(GL_CULL_FACE);
}

void DeviceOpenGL::clear(
	const Color* color,
	bool depth) noexcept
{
	GLbitfield clearMask = 0;
	if (color != nullptr)
	{
		clearMask |= GL_COLOR_BUFFER_BIT;
		glClearColor(color->r, color->g, color->b, color->a);
	}

	if (depth)
	{
		clearMask |= GL_DEPTH_BUFFER_BIT;
	}
	glClear(clearMask);
}

void DeviceOpenGL::enableVSync(bool vSync) noexcept
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

void DeviceOpenGL::setFramebuffer(Framebuffer* frameBuffer) noexcept
{
	if (frameBuffer == nullptr)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		frameBuffer->bind();
	}
}

void DeviceOpenGL::setViewport(const Rectangle2u& viewport) noexcept
{
	const auto& min = viewport.getMin();
	const auto& max = viewport.getMax();
	glViewport(
		static_cast<GLint>(min.x),
		static_cast<GLint>(min.y),
		static_cast<GLsizei>(max.x - min.x),
		static_cast<GLsizei>(max.y - min.y));
}

std::unique_ptr<Geometry> DeviceOpenGL::createBackendGeometry(
	VertexFormat vertexFormat,
	u32 vertexCount,
	const float* vertices,
	u32 indexCount,
	const u32* indices)
{
	return std::make_unique<GeometryOpenGL>(
		vertexFormat,
		vertexCount,
		vertices,
		indexCount,
		indices);
}

std::unique_ptr<Shader> DeviceOpenGL::createBackendShader(
	const char* vertexShader,
	const char* fragmentShader)
{
	return std::make_unique<ShaderOpenGL>(vertexShader, fragmentShader);
}

std::unique_ptr<Texture> DeviceOpenGL::createBackendTexture(
	const void* data,
	const Point2u& size,
	TextureFormat format,
	const TextureParameters& parameters)
{
	return std::make_unique<TextureOpenGL>(
		data,
		size,
		format,
		parameters);
}

std::unique_ptr<TextureFramebuffer> DeviceOpenGL::createBackendTextureFramebuffer(
	Texture* color,
	Texture* depth)
{
	return std::make_unique<TextureFramebufferOpenGL>(color, depth);
}

void DeviceOpenGL::bindTexture(const Texture* texture, u32 slot) noexcept
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

void DeviceOpenGL::setFaceCulling(bool back, bool front) noexcept
{
	GLenum cullMode = GL_NONE;
	if (back && front)
	{
		cullMode = GL_FRONT_AND_BACK;
	}
	else if (back)
	{
		cullMode = GL_BACK;
	}
	else if (front)
	{
		cullMode = GL_FRONT;
	}
	glCullFace(cullMode);
}

void DeviceOpenGL::setBlending(bool enabled) noexcept
{
	if (enabled)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

// End of the namespace gltut
}
