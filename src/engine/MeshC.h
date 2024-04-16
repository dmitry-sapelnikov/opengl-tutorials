#ifndef OPENGL_TUTORIALS_MESH_C_H
#define OPENGL_TUTORIALS_MESH_C_H

// Includes
#include "engine/Mesh.h"
#include "engine/Renderer.h"
#include <vector>

namespace gltut
{

class MeshC final : public Mesh
{
public:
	/// Constructor
	MeshC(
		Renderer& renderer,
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount);

	/// Destructor
	~MeshC() final;

	/// Renders the mesh
	void render() const noexcept final;

	/// Returns the shader program
	unsigned getShaderProgram() const noexcept final;

	///	Sets the shader program
	void setShaderProgram(unsigned shaderProgram) noexcept final;

private:
	/// The renderer
	Renderer& mRenderer;

	/// The vertices
	std::vector<float> mVertices;

	/// The indices
	std::vector<u32> mIndices;

	/// The vertex buffer object
	unsigned mVBO = 0;

	/// The vertex array object
	unsigned mVAO = 0;

	/// The element buffer object
	unsigned mEBO = 0;

	/// Shader program
	unsigned mShaderProgram = 0;
};

// End of the namespace gltut
}

#endif
