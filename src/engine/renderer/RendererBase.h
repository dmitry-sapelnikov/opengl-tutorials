#pragma once

// Includes
#include <unordered_map>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/window/EventHandler.h"

namespace gltut
{

/// Renderer base class
class RendererBase : public Renderer, public EventHandler, public NonCopyable
{
public:
	/// Invalid mesh index
	static constexpr u32 INVALID_MESH_INDEX = std::numeric_limits<u32>::max();

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
		const u8* data,
		u32 width,
		u32 height,
		u32 channelCount) noexcept final;

	/// Loads a texture
	Texture* loadTexture(const char* path) noexcept final;

	/// Removes a texture
	void removeTexture(Texture* texture) noexcept final;

	/// Creates a solid color texture
	Texture* createSolidColorTexture(
		float r,
		float g,
		float b,
		float a = 1.0f) noexcept final;

	/// Called when an event occurs
	void onEvent(const Event& event) noexcept final;

private:
	/// Called when the window is resized
	virtual void onResize(const Point2u& size) noexcept = 0;

	/// Creates a shader for a specific graphics backend
	virtual Mesh* createBackendMesh(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) noexcept = 0;

	/// Creates a shader for a specific graphics backend
	virtual Shader* createBackendShader(
		const char* vertexShader,
		const char* fragmentShader) noexcept = 0;

	/// Creates a texture for a specific graphics backend
	virtual Texture* createBackendTexture(
		const u8* data,
		u32 width,
		u32 height,
		u32 channelCount) noexcept = 0;

	/// Meshes
	std::vector<std::unique_ptr<Mesh>> mMeshes;

	/// Shaders
	std::vector<std::unique_ptr<Shader>> mShaders;

	/// Textures
	std::vector<std::unique_ptr<Texture>> mTextures;

	/// Solid color textures
	std::unordered_map<u32, Texture*> mSolidColorTextures;
};

// End of the namespace gltut
}
