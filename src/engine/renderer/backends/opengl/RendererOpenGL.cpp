// Includes
#include "RendererOpenGL.h"

#include <iostream>
#undef APIENTRY
#include <Windows.h>

#include "engine/core/Check.h"
#include "MeshOpenGL.h"
#include "ShaderOpenGL.h"
#include "TextureOpenGL.h"

#include "../../../core/File.h"

namespace gltut
{

// Define the function pointer type
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);


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

void RendererOpenGL::enableVSync(bool vSync) noexcept
{
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
		(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	GLTUT_ASSERT(wglSwapIntervalEXT != nullptr);
	wglSwapIntervalEXT(vSync ? 1 : 0);
}

Mesh* RendererOpenGL::createBackendMesh(
	VertexFormat vertexFormat,
	u32 vertexCount,
	const float* vertices,
	u32 indexCount,
	const u32* indices) noexcept
{
	Mesh* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = new MeshOpenGL(
			vertexFormat,
			vertexCount,
			vertices,
			indexCount,
			indices);
	GLTUT_CATCH_ALL_END("Failed to create mesh")
	return result;
}

Shader* RendererOpenGL::createBackendShader(
	const char* vertexShader,
	const char* fragmentShader) noexcept
{
	Shader* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = new ShaderOpenGL(vertexShader, fragmentShader);
	GLTUT_CATCH_ALL_END("Failed to create shader program")
	return result;
}

Texture* RendererOpenGL::createBackendTexture(
	const u8* data,
	u32 width,
	u32 height,
	u32 channelCount) noexcept
{
	Texture* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = new TextureOpenGL(
			data,
			width,
			height,
			channelCount);
	GLTUT_CATCH_ALL_END("Failed to create texture from data")
	return result;
}

void RendererOpenGL::onResize(const Point2u& size) noexcept
{
	glViewport(0, 0, size.x, size.y);
}

// End of the namespace gltut
}
