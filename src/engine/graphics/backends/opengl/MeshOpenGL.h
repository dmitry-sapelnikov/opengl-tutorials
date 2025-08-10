#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/graphics/mesh/Mesh.h"

namespace gltut
{

class MeshOpenGL final : public Mesh, public NonCopyable
{
public:
	/// Constructor
	MeshOpenGL(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices);

	/// Destructor
	~MeshOpenGL() final;

	/// Renders the mesh
	void render() const noexcept final;

private:
	/// Indices count
	u32 mIndexCount;

	/// The vertex buffer object
	u32 mVertexBuffer = 0;

	/// The element buffer object
	u32 mIndexBuffer = 0;

	/// The vertex array object
	u32 mVertexArray = 0;
};

// End of the namespace gltut
}
