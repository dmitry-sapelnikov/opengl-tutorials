#ifndef OPENGL_TUTORIALS_RENDERER_H
#define OPENGL_TUTORIALS_RENDERER_H

// Includes
#include "core/Types.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

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

	/// Allocates a vertex buffer
	virtual unsigned allocateVertexBuffer(float* vertices, u32 count) noexcept = 0;

	/// Allocates an index buffer
	virtual unsigned allocateIndexBuffer(u32* indices, u32 count) noexcept = 0;

	/// Allocates a vertex array
	virtual unsigned allocateVertexArray(
		VertexFormat vertexFormat,
		unsigned vertexBuffer,
		unsigned indexBuffer) noexcept = 0;
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
		const u8* data,
		u32 width,
		u32 height,
		u32 channels) noexcept = 0;

	/// Loads a texture
	virtual Texture* loadTexture(const char* path) noexcept = 0;

	/// Removes a texture
	virtual void removeTexture(Texture* texture) noexcept = 0;

	/// Enables or disables vertical synchronization
	virtual void enableVSync(bool vSync) noexcept = 0;
};

// End of the namespace gltut
}

#endif
