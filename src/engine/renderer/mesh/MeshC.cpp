// Includes
#include "MeshC.h"
#include "engine/core/Check.h"

namespace gltut
{
//	Global classes
MeshC::MeshC(
	RendererBase& renderer,
	VertexFormat vertexFormat,
	u32 vertexCount,
	const float* vertexData,
	u32 indexCount,
	const u32* indexData) :

	mRenderer(renderer),
	mVertexFormat(vertexFormat)
{
	GLTUT_ASSERT(vertexCount > 0);
	GLTUT_ASSERT(vertexData != nullptr);

	mVertices.assign(vertexData, vertexData + vertexCount * vertexFormat.getTotalSize());

	GLTUT_ASSERT(indexData != nullptr);
	GLTUT_ASSERT(indexCount > 0);
	GLTUT_ASSERT(indexCount % 3 == 0);
	mIndices.assign(indexData, indexData + indexCount);

	mIndexInRenderer = mRenderer.addMesh(*this);
	GLTUT_ASSERT(mIndexInRenderer != RendererBase::INVALID_MESH_INDEX);
}

MeshC::~MeshC()
{
	if (mIndexInRenderer != RendererBase::INVALID_MESH_INDEX)
	{
		mRenderer.removeMesh(mIndexInRenderer);
	}
}

// End of the namespace gltut
}
