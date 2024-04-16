// Includes
#include "MeshC.h"
#include "engine/core/Assert.h"
#include "engine/core/Types.h"
#include <glad/glad.h>

namespace gltut
{

MeshC::MeshC(float* vertices,
	u32 vertexCount,
	u32* indices,
	u32 indexCount)
{
	GLTUT_ASSERT(vertices != nullptr);
	GLTUT_ASSERT(vertexCount > 0);
	GLTUT_ASSERT(vertexCount % 3 == 0);
	mVertices.assign(vertices, vertices + vertexCount);

	GLTUT_ASSERT(indexCount > 0);
	GLTUT_ASSERT(indexCount % 3 == 0);
	mIndices.assign(indices, indices + indexCount);

	//	Create the vertex array object
	glGenVertexArrays(1, &mVAO);
	GLTUT_ASSERT(mVAO != 0);
	glBindVertexArray(mVAO);

	//	Create the vertex buffer object
	glGenBuffers(1, &mVBO);
	GLTUT_ASSERT(mVBO != 0);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * mVertices.size(),
		&mVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		nullptr);

	glEnableVertexAttribArray(0);

	//	Unbind the vertex array object
	glBindVertexArray(0);

	//	Unbind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//	Create the element buffer object
	glGenBuffers(1, &mEBO);
	GLTUT_ASSERT(mEBO != 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(u32) * mIndices.size(),
		&mIndices[0],
		GL_STATIC_DRAW);

	//	Unbind the element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

MeshC::~MeshC()
{
	if (mVAO != 0)
	{
		glDeleteVertexArrays(1, &mVAO);
	}

	if (mVBO != 0)
	{
		glDeleteBuffers(1, &mVBO);
	}

	if (mEBO != 0)
	{
		glDeleteBuffers(1, &mEBO);
	}
}

void MeshC::render() const noexcept
{
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glDrawElements(
		GL_TRIANGLES,
		static_cast<u32>(mIndices.size()),
		GL_UNSIGNED_INT,
		nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// End of the namespace gltut
}
