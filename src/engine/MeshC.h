#ifndef OPENGL_TUTORIALS_MESH_C_H
#define OPENGL_TUTORIALS_MESH_C_H

// Includes
#include "engine/Mesh.h"
#include "engine/Renderer.h"
#include <vector>

namespace gltut
{

class MeshC : public Mesh
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
	~MeshC() override;

	/// Renders the mesh
	void render() const noexcept override;

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
};

// End of the namespace gltut
}

#endif
