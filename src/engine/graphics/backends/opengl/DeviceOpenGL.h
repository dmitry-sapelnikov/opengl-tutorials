#pragma once

// Includes
#include <vector>
#include <memory>
#include "../../GraphicsDeviceBase.h"
#include "./framebuffer/WindowFramebufferOpenGL.h"

namespace gltut
{
/// OpenGL device
class DeviceOpenGL final : public GraphicsDeviceBase
{
public:
	/// Constructor
	DeviceOpenGL(Window& window);

	/// Clears the current render target with a specific color
	void clear(
		const Color* color,
		bool depth) noexcept final;

	/// Enables or disables vertical synchronization
	void enableVSync(bool vSync) noexcept final;

	/// Returns the default (window) framebuffer
	Framebuffer* getDefaultFramebuffer() const noexcept final
	{
		return mWindowFramebuffer.get();
	}

	std::unique_ptr<Geometry> createBackendGeometry(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) final;

	/// Creates a shader
	std::unique_ptr<Shader> createBackendShader(
		const char* vertexShader,
		const char* fragmentShader) final;

	/// Creates a shader uniform buffer
	std::unique_ptr<ShaderUniformBuffer> createBackendShaderUniformBuffer(
		u32 sizeInBytes) final;

	/// Creates a texture
	std::unique_ptr<Texture2> createBackendTexture2(
		const TextureData& data,
		const TextureParameters& parameters) final;

	/// Creates a texture cubemap for a specific graphics backend
	std::unique_ptr<TextureCubemap> createBackendTextureCubemap(
		const TextureData& minusXData,
		const TextureData& plusXData,
		const TextureData& minusYData,
		const TextureData& plusYData,
		const TextureData& minusZData,
		const TextureData& plusZData,
		const TextureParameters& parameters) final;

	/// Creates a framebuffer
	std::unique_ptr<TextureFramebuffer> createBackendTextureFramebuffer(
		Texture2* color,
		Texture2* depth) final;

	/// Binds a texture to a slot
	void bindTexture(const Texture* texture, u32 slot) noexcept final;

	/// Binds a shader uniform buffer to a binding point
	void bindShaderUniformBuffer(
		const ShaderUniformBuffer* buffer,
		u32 bindingPoint) noexcept final;

	/// Set face cull mode
	void setFaceCulling(FaceCullingMode mode) noexcept final;

	/// Enable or disables blending
	void setBlending(bool enabled) noexcept final;

	/// Sets the depth function
	void setDepthTest(DepthTestMode mode) noexcept final;

	void setPolygonFill(
		PolygonFillMode mode,
		float size = 1.0f,
		bool enableSizeInShader = false) noexcept final;

private:
	/// Sets a framebuffer for rendering
	void setFramebuffer(Framebuffer* frameBuffer) noexcept final;

	/// Sets the viewport for rendering
	void setViewport(const Rectangle2u& viewport) noexcept final;

	/// The window framebuffer
	std::unique_ptr<WindowFramebufferOpenGL> mWindowFramebuffer;
};

// End of the namespace gltut
}
