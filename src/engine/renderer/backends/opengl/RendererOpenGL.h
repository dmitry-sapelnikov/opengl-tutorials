#pragma once

// Includes
#include <vector>
#include <memory>
#include <glad/glad.h>

#include "../../RendererBase.h"

namespace gltut
{
/// OpenGL renderer
class RendererOpenGL final : public RendererBase
{
public:
	/// Constructor
	RendererOpenGL(void* deviceContext);

	/// Sets the clear color
	void setClearColor(float r, float g, float b, float a) noexcept final;

	/// Clears the screen
	void clear() noexcept final;

	/// Enables or disables vertical synchronization
	void enableVSync(bool vSync) noexcept final;

private:
	Mesh* createBackendMesh(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) noexcept final;

	/// Creates a shader
	Shader* createBackendShader(
		const char* vertexShader,
		const char* fragmentShader) noexcept final;

	/// Creates a texture
	Texture* createBackendTexture(
		const u8* data,
		u32 width,
		u32 height,
		u32 channelCount) noexcept final;

private:
	/// Called when the window is resized
	void onResize(const Point2u& size) noexcept final;

	///	The window
	void* mDeviceContext;
};

// End of the namespace gltut
}
