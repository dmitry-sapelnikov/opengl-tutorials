#ifndef OPENGL_TUTORIALS_MESH_C_H
#define OPENGL_TUTORIALS_MESH_C_H

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Mesh.h"
#include <array>
#include <vector>
#include "../RendererBase.h"

namespace gltut
{

class MeshC final : public Mesh, public NonCopyable
{
public:
	/// Constructor
	MeshC(
		RendererBase& renderer,
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertexData,
		u32 indexCount,
		const u32* indexData);

	/// Destructor
	~MeshC() final;

	/// Returns the vertices
	float* getVertices() const noexcept final
	{
		return const_cast<float*>(mVertices.data());
	}

	/// Returns the vertex count
	u32 getVertexCount() const noexcept final
	{
		return static_cast<u32>(mVertices.size() / mVertexFormat.getTotalSize());
	}

	/// Returns the indices
	u32* getIndices() const noexcept final
	{
		return const_cast<u32*>(mIndices.data());
	}

	/// Returns the index count
	u32 getIndexCount() const noexcept final
	{
		return static_cast<u32>(mIndices.size());
	}

	/// Returns the vertex format
	VertexFormat getVertexFormat() const noexcept final
	{
		return mVertexFormat;
	}

	u32 getIndexInRenderer() const noexcept
	{
		return mIndexInRenderer;
	}

private:
	/// The renderer
	RendererBase& mRenderer;

	/// The vertex format
	VertexFormat mVertexFormat;

	/// The vertices
	std::vector<float> mVertices;

	/// The indices
	std::vector<u32> mIndices;

	/// Index in renderer
	u32 mIndexInRenderer;
};

// End of the namespace gltut
}

#endif
