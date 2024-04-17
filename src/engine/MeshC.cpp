// Includes
#include "MeshC.h"
#include "engine/core/Check.h"

namespace gltut
{
//	Global classes
MeshC::MeshC(
	Renderer& renderer,
	VertexFormat vertexFormat,
	float* vertices,
	u32 vertexCount,
	u32* indices,
	u32 indexCount) :

	mRenderer(renderer)
{
	GLTUT_ASSERT(vertices != nullptr);
	GLTUT_ASSERT(vertexCount > 0);
	GLTUT_ASSERT(vertexCount % 3 == 0);
	mVertices.assign(vertices, vertices + vertexCount);

	GLTUT_ASSERT(indices != nullptr);
	GLTUT_ASSERT(indexCount > 0);
	GLTUT_ASSERT(indexCount % 3 == 0);
	mIndices.assign(indices, indices + indexCount);

	mVBO = mRenderer.allocateVertexBuffer(
		&mVertices[0],
		static_cast<u32>(mVertices.size()));

	mEBO = mRenderer.allocateIndexBuffer(
		&mIndices[0],
		static_cast<u32>(mIndices.size()));

	mVAO = mRenderer.allocateVertexArray(vertexFormat, mVBO, mEBO);
}

MeshC::~MeshC()
{
	mRenderer.freeVertexArray(mVAO);
	mRenderer.freeBuffer(mVBO);
	mRenderer.freeBuffer(mEBO);
}

void MeshC::render() const noexcept
{
	if (mShader != 0)
	{
		mShader->use();
	}
	mRenderer.setVertexArray(mVAO);
	mRenderer.drawIndexedTriangles(static_cast<u32>(mIndices.size()));
	mRenderer.setVertexArray(0);
}

Shader* MeshC::getShader() const noexcept
{
	return mShader;
}

void MeshC::setShader(Shader* shader) noexcept
{
	mShader = shader;
}

// End of the namespace gltut
}
