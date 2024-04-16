// Includes
#include "MeshC.h"
#include "engine/core/Assert.h"

namespace gltut
{
//	Global classes
MeshC::MeshC(
	Renderer& renderer,
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

	mVAO = mRenderer.allocateVertexArray(mVBO, mEBO);
}

MeshC::~MeshC()
{
	mRenderer.freeVertexArray(mVAO);
	mRenderer.freeBuffer(mVBO);
	mRenderer.freeBuffer(mEBO);
}

void MeshC::render() const noexcept
{
	if (mShaderProgram != 0)
	{
		mRenderer.setShaderProgram(mShaderProgram);
	}
	mRenderer.setVertexArray(mVAO);
	mRenderer.drawIndexedTriangles(static_cast<u32>(mIndices.size()));
	mRenderer.setVertexArray(0);
}

unsigned MeshC::getShaderProgram() const noexcept
{
	return mShaderProgram;
}

void MeshC::setShaderProgram(unsigned shaderProgram) noexcept
{
	mShaderProgram = shaderProgram;
}

// End of the namespace gltut
}
