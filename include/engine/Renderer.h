#ifndef OPENGL_TUTORIALS_RENDERER_H
#define OPENGL_TUTORIALS_RENDERER_H

// Includes
#include "core/Types.h"
#include "Shader.h"

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

	/// Frees a vertex/index buffer
	virtual void freeBuffer(unsigned buffer) noexcept = 0;

	/// Allocates a vertex array
	virtual unsigned allocateVertexArray(unsigned vertexBuffer, unsigned indexBuffer) noexcept = 0;

	/// Frees a vertex array
	virtual void freeVertexArray(unsigned vertexArray) noexcept = 0;

	/// Sets a vertex buffer
	virtual void setVertexBuffer(unsigned buffer) noexcept = 0;

	/// Sets an index buffer
	virtual void setIndexBuffer(unsigned buffer) noexcept = 0;

	/// Sets an vertex array
	virtual void setVertexArray(unsigned vertexArray) noexcept = 0;

	/// Draws the indexed triangles
	virtual void drawIndexedTriangles(u32 indicesCount) noexcept = 0;

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
};

// End of the namespace gltut
}

#endif
