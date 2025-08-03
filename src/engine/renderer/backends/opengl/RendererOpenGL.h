#pragma once

// Includes
#include <vector>
#include <memory>
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

	/// Clears the viewport
	void clear() noexcept final;

	/// Enables or disables vertical synchronization
	void enableVSync(bool vSync) noexcept final;

	/// Sets the viewport for the current render target
	void setViewport(const Rectangle2u& rectangle) noexcept final;

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
		const void* data,
		u32 width,
		u32 height,
		Texture::Format format,
		Texture::FilterMode minFilter,
		Texture::FilterMode magFilter,
		Texture::WrapMode wrapMode) noexcept final;

	/// Binds a texture to a slot
	void bindTexture(Texture* texture, u32 slot) noexcept final;

private:
	///	The window
	void* mDeviceContext;
};

// End of the namespace gltut
}
