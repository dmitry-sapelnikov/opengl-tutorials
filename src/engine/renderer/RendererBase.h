#pragma once

// Includes
#include <unordered_map>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/window/Window.h"

namespace gltut
{

/// Renderer base class
class RendererBase : public Renderer, public NonCopyable
{
public:
	/// Invalid mesh index
	static constexpr u32 INVALID_MESH_INDEX = std::numeric_limits<u32>::max();

	/// Constructor
	RendererBase(Window& window) noexcept;

	/// Creates a mesh
	Mesh* createMesh(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) noexcept final;

	/// Removes a mesh
	void removeMesh(Mesh* mesh) noexcept final;

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

	/// Creates a texture
	Texture* createTexture(
		const void* data,
		u32 width,
		u32 height,
		Texture::Format format,
		Texture::FilterMode minFilter,
		Texture::FilterMode magFilter,
		Texture::WrapMode wrapMode) noexcept final;

	/// Loads a texture
	Texture* loadTexture(
		const char* imagePath,
		Texture::FilterMode minFilter,
		Texture::FilterMode magFilter,
		Texture::WrapMode wrapMode) noexcept final;

	/// Creates a solid color texture
	Texture* createSolidColorTexture(
		float r,
		float g,
		float b,
		float a = 1.0f) noexcept final;

	/// Removes a texture
	void removeTexture(Texture* texture) noexcept final;

	/**
		\brief Creates a framebuffer
		\note At least one of texture parameters must be non-null
	*/
	Framebuffer* createFramebuffer(
		Texture* color,
		Texture* depth) noexcept final;

	/// Removes a framebuffer
	void removeFramebuffer(Framebuffer* frameBuffer) noexcept final;

	/// Activates a framebuffer
	void activateFramebuffer(
		Framebuffer* frameBuffer,
		Rectangle2u* viewport) noexcept final;

	/// Returns the window associated with this renderer
	Window& getWindow() noexcept
	{
		return mWindow;
	}

private:
	// Sets the framebuffer for rendering
	virtual void setFramebuffer(Framebuffer* frameBuffer) noexcept = 0;

	// Sets the viewport for rendering
	virtual void setViewport(const Rectangle2u& viewport) noexcept = 0;

	/// Creates a shader for a specific graphics backend
	virtual std::unique_ptr<Mesh> createBackendMesh(
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
		u32 width,
		u32 height,
		Texture::Format format,
		Texture::FilterMode minFilter,
		Texture::FilterMode magFilter,
		Texture::WrapMode wrapMode) = 0;

	virtual std::unique_ptr<Framebuffer> createBackendFramebuffer(
		Texture* color,
		Texture* depth) = 0;

	/// The window associated with this renderer
	Window& mWindow;

	/// Meshes
	std::vector<std::unique_ptr<Mesh>> mMeshes;

	/// Shaders
	std::vector<std::unique_ptr<Shader>> mShaders;

	/// Textures
	std::vector<std::unique_ptr<Texture>> mTextures;

	/// Solid color textures
	std::unordered_map<u32, Texture*> mSolidColorTextures;

	/// Framebuffers
	std::vector<std::unique_ptr<Framebuffer>> mFramebuffers;
};

// End of the namespace gltut
}
