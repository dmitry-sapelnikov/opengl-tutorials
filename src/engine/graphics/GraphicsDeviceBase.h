#pragma once

// Includes
#include <unordered_map>
#include "engine/core/NonCopyable.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/window/Window.h"

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

	/// Creates a geometry
	Geometry* createGeometry(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) noexcept final;

	/// Removes a geometry
	void removeGeometry(Geometry* geometry) noexcept final;

	/// Creates a shader from strings
	Shader* createShader(
		const char* vertexShader,
		const char* fragmentShader) noexcept final;

	/// Creates a shader from files
	Shader* loadShader(
		const char* vertexShaderPath,
		const char* fragmentShaderPath) noexcept final;

	/// Removes a shader
	void removeShader(Shader* shader) noexcept final;

	/// Returns textures
	TextureManager* getTextures() noexcept final
	{
		return &mTextures;
	}

	/// Creates a solid color texture
	const Texture* createSolidColorTexture(
		float r,
		float g,
		float b,
		float a = 1.0f) noexcept final;

	/**
		\brief Creates a framebuffer
		\note At least one of texture parameters must be non-null
	*/
	TextureFramebuffer* createTextureFramebuffer(
		Texture* color,
		Texture* depth) noexcept final;

	/// Removes a framebuffer
	void removeTextureFramebuffer(TextureFramebuffer* frameBuffer) noexcept final;

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
	virtual std::unique_ptr<Texture> createBackendTexture(
		const void* data,
		const Point2u& size,
		const TextureFormat format,
		const TextureParameters& parameters) = 0;

	virtual std::unique_ptr<TextureFramebuffer> createBackendTextureFramebuffer(
		Texture* color,
		Texture* depth) = 0;

private:
	// Sets the framebuffer for rendering
	virtual void setFramebuffer(Framebuffer* frameBuffer) noexcept = 0;

	// Sets the viewport for rendering
	virtual void setViewport(const Rectangle2u& viewport) noexcept = 0;

	/// The window associated with this device
	Window& mWindow;

	/// Geometryes
	std::vector<std::unique_ptr<Geometry>> mGeometryes;

	/// Shaders
	std::vector<std::unique_ptr<Shader>> mShaders;

	/// Textures
	TextureManagerC mTextures;

	/// Solid color textures
	std::unordered_map<u32, const Texture*> mSolidColorTextures;

	/// Framebuffers
	std::vector<std::unique_ptr<TextureFramebuffer>> mFramebuffers;
};

// End of the namespace gltut
}
