#pragma once

// Includes
#include "engine/core/Types.h"
#include "engine/renderer/mesh/Mesh.h"
#include "engine/renderer/shader/Shader.h"
#include "engine/renderer/Texture.h"

namespace gltut
{
//	Global classes
///	The renderer
class Renderer
{
public:
	/// Virtual destructor
	virtual ~Renderer() noexcept = default;

	/// Sets the clear color
	virtual void setClearColor(float r, float g, float b, float a) noexcept = 0;

	/// Clears the screen
	virtual void clear() noexcept = 0;

	/// Creates a mesh
	virtual Mesh* createMesh(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) noexcept = 0;

	/// Removes a mesh
	virtual void removeMesh(Mesh* mesh) noexcept = 0;

	/// Creates a shader from strings
	virtual Shader* createShader(
		const char* vertexShader,
		const char* fragmentShader) noexcept = 0;

	/// Creates a shader from files
	virtual Shader* loadShader(
		const char* vertexShaderPath,
		const char* fragmentShaderPath) noexcept = 0;

	/// Removes a shader
	virtual void removeShader(Shader* shader) noexcept = 0;

	/// Creates a texture
	virtual Texture* createTexture(
		const void* data,
		u32 width,
		u32 height,
		Texture::Format format = Texture::Format::RGBA,
		Texture::FilterMode minFilter = Texture::FilterMode::LINEAR_MIPMAP,
		Texture::FilterMode magFilter = Texture::FilterMode::LINEAR,
		Texture::WrapMode wrapMode = Texture::WrapMode::REPEAT) noexcept = 0;

	/// Loads a texture
	virtual Texture* loadTexture(
		const char* imagePath,
		Texture::FilterMode minFilter = Texture::FilterMode::LINEAR_MIPMAP,
		Texture::FilterMode magFilter = Texture::FilterMode::LINEAR,
		Texture::WrapMode wrapMode = Texture::WrapMode::REPEAT) noexcept = 0;

	/// Removes a texture
	virtual void removeTexture(Texture* texture) noexcept = 0;

	/// Binds a texture to a slot
	virtual void bindTexture(Texture* texture, u32 slot) noexcept = 0;

	/// Enables or disables vertical synchronization
	virtual void enableVSync(bool vSync) noexcept = 0;

	/// Creates a solid color texture
	virtual Texture* createSolidColorTexture(
		float r,
		float g,
		float b,
		float a = 1.0f) noexcept = 0;
};

// End of the namespace gltut
}
