#ifndef OPENGL_TUTORIALS_RENDERER_OPEN_GL_H
#define OPENGL_TUTORIALS_RENDERER_OPEN_GL_H

// Includes
#include "engine/Renderer.h"

namespace gltut
{
/// OpenGL renderer
class RendererOpenGL final : public Renderer
{
public:
	/// Constructor
	RendererOpenGL();

	/// Sets the clear color
	void setClearColor(float r, float g, float b, float a) noexcept final;

	/// Clears the screen
	void clear() noexcept final;

	/// Allocates a vertex buffer
	unsigned allocateVertexBuffer(float* vertices, u32 count) noexcept final;

	/// Allocates an index buffer
	unsigned allocateIndexBuffer(u32* indices, u32 count) noexcept final;

	/// Frees a vertex/index buffer
	void freeBuffer(unsigned buffer) noexcept final;

	/// Allocates a vertex array
	unsigned allocateVertexArray(unsigned vertexBuffer, unsigned indexBuffer) noexcept final;

	/// Frees a vertex array
	void freeVertexArray(unsigned vertexArray) noexcept final;

	/// Sets a vertex buffer
	void setVertexBuffer(unsigned buffer) noexcept final;

	/// Sets an index buffer
	void setIndexBuffer(unsigned buffer) noexcept final;

	/// Sets an vertex array
	void setVertexArray(unsigned vertexArray) noexcept final;

	/// Draws the indexed triangles
	void drawIndexedTriangles(u32 indicesCount) noexcept final;

	/// Creates a shader program
	unsigned createShaderProgram(
		const char* vertexShader,
		const char* fragmentShader) noexcept final;

	/// Returns the current shader program
	unsigned getShaderProgram() const noexcept final;

	/**
		\brief Sets a shader program
		\note Repetitive calls does not degrade performance
	*/
	void setShaderProgram(unsigned program) noexcept final;

	/// Frees a shader program
	void freeShaderProgram(unsigned program) noexcept final;

private:
	unsigned mShaderProgram = 0;
};

// End of the namespace gltut
}

#endif
