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

	/// Returns the window framebuffer
	Framebuffer* getWindowFramebuffer() const noexcept final
	{
		return mWindowFramebuffer.get();
	}

private:
	void setFramebuffer(Framebuffer* frameBuffer) noexcept final;

	void setViewport(const Rectangle2u& viewport) noexcept final;

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

	/// Creates a texture
	std::unique_ptr<Texture> createBackendTexture(
		const void* data,
		const Point2u& size,
		TextureFormat format,
		const TextureParameters& parameters) final;

	/// Creates a framebuffer
	std::unique_ptr<TextureFramebuffer> createBackendTextureFramebuffer(
		Texture* color,
		Texture* depth) final;

	/// Binds a texture to a slot
	void bindTexture(const Texture* texture, u32 slot) noexcept final;

	/// The window framebuffer
	std::unique_ptr<WindowFramebufferOpenGL> mWindowFramebuffer;
};

// End of the namespace gltut
}
