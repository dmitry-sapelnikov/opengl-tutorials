#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/window/Window.h"

#include "./geometry/GeometryManagerC.h"
#include "./framebuffer/FramebufferManagerC.h"
#include "./shader/ShaderManagerC.h"
#include "./texture/TextureManagerC.h"

namespace gltut
{

/// GraphicsDevice base class
class GraphicsDeviceBase : public GraphicsDevice, public NonCopyable
{
public:
	/// Invalid geometry index
	static constexpr u32 INVALID_MESH_INDEX = std::numeric_limits<u32>::max();

	/// Constructor
	GraphicsDeviceBase(Window& window) noexcept;

	/// Returns the geometry manager
	GeometryManager* getGeometries() noexcept final
	{
		return &mGeometries;
	}

	/// Returns the framebuffer manager
	FramebufferManager* getFramebuffers() noexcept final
	{
		return &mFramebuffers;
	}

	/// Returns the shader manager
	ShaderManager* getShaders() noexcept final
	{
		return &mShaders;
	}

	/// Returns texture manager	
	TextureManager* getTextures() noexcept final
	{
		return &mTextures;
	}

	/// Binds a framebuffer
	void bindFramebuffer(
		Framebuffer* framebuffer,
		Rectangle2u* viewport) noexcept final;

	/// Returns the window associated with this device
	Window& getWindow() noexcept
	{
		return mWindow;
	}

	/// Creates a shader for a specific graphics backend
	virtual std::unique_ptr<Geometry> createBackendGeometry(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) = 0;

	/// Creates a shader for a specific graphics backend
	virtual std::unique_ptr<Shader> createBackendShader(
		const char* vertexShader,
		const char* fragmentShader) = 0;

	/// Creates a texture for a specific graphics backend
	virtual std::unique_ptr<Texture2> createBackendTexture2(
		const TextureData& data,
		const TextureParameters& parameters) = 0;

	/// Creates a texture cubemap for a specific graphics backend
	virtual std::unique_ptr<TextureCubemap> createBackendTextureCubemap(
		const TextureData& minusXData,
		const TextureData& plusXData,
		const TextureData& minusYData,
		const TextureData& plusYData,
		const TextureData& minusZData,
		const TextureData& plusZData,
		const TextureParameters& parameters) = 0;

	virtual std::unique_ptr<TextureFramebuffer> createBackendTextureFramebuffer(
		Texture2* color,
		Texture2* depth) = 0;

	virtual Framebuffer* getDefaultFramebuffer() const noexcept = 0;

private:
	// Sets the framebuffer for rendering
	virtual void setFramebuffer(Framebuffer* frameBuffer) noexcept = 0;

	// Sets the viewport for rendering
	virtual void setViewport(const Rectangle2u& viewport) noexcept = 0;

	/// The window associated with this device
	Window& mWindow;

	/// Geometryes
	GeometryManagerC mGeometries;

	/// Framebuffers
	FramebufferManagerC mFramebuffers;

	/// Shaders
	ShaderManagerC mShaders;

	/// Textures
	TextureManagerC mTextures;
};

// End of the namespace gltut
}
