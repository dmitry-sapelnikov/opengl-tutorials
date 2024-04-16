#ifndef OPENGL_TUTORIALS_RENDERER_OPEN_GL_H
#define OPENGL_TUTORIALS_RENDERER_OPEN_GL_H

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/Renderer.h"
#include <vector>
#include <memory>

namespace gltut
{
/// OpenGL renderer
class RendererOpenGL final : public Renderer, public NonCopyable
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

	/// Creates a shader
	Shader* createShader(
		const char* vertexShader,
		const char* fragmentShader) noexcept final;

	/// Loads a shader from files
	Shader* loadShader(
		const char* vertexShaderPath,
		const char* fragmentShaderPath) noexcept final;

	/// Removes a shader
	void removeShader(Shader* shader) noexcept final;

private:
	/// Shaders
	std::vector<std::unique_ptr<Shader>> mShaders;
};

// End of the namespace gltut
}

#endif
