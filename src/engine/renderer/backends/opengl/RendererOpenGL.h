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

	/// Activates a framebuffer
	void activateFramebuffer(Framebuffer* frameBuffer) noexcept final;

	/// Enables or disables vertical synchronization
	void enableVSync(bool vSync) noexcept final;

	/// Sets the viewport for the current render target
	void setViewport(const Rectangle2u& rectangle) noexcept final;

private:
	std::unique_ptr<Mesh> createBackendMesh(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) final;

	/// Creates a shader
	std::unique_ptr<Shader> createBackendShader(
		const char* vertexShader,
		const char* fragmentShader) final;

	/// Creates a texture
	std::unique_ptr<Texture> createBackendTexture(
		const void* data,
		u32 width,
		u32 height,
		Texture::Format format,
		Texture::FilterMode minFilter,
		Texture::FilterMode magFilter,
		Texture::WrapMode wrapMode) final;

	/// Creates a framebuffer
	std::unique_ptr<Framebuffer> createBackendFramebuffer(
		Texture* color,
		Texture* depth) final;

	/// Binds a texture to a slot
	void bindTexture(Texture* texture, u32 slot) noexcept final;

private:
	///	The window
	void* mDeviceContext;
};

// End of the namespace gltut
}
