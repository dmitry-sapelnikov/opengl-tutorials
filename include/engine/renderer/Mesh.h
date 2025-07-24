#ifndef OPENGL_TUTORIALS_MESH_H
#define OPENGL_TUTORIALS_MESH_H

// Includes
#include "engine/renderer/VertexFormat.h"

namespace gltut
{

/// The class represents a triangle mesh
class Mesh
{
public:
	/// Virtual destructor
	virtual ~Mesh() noexcept = default;

	/// Returns the vertices (const version)
	virtual float* getVertices() const noexcept = 0;

	/// Returns the vertex count
	virtual u32 getVertexCount() const noexcept = 0;

	/// Returns the indices (const version)
	virtual u32* getIndices() const noexcept = 0;

	/// Returns the index count
	virtual u32 getIndexCount() const noexcept = 0;

	/// Returns the vertex format
	virtual VertexFormat getVertexFormat() const noexcept = 0;

	/// Returns the index in the renderer
	virtual u32 getIndexInRenderer() const noexcept = 0;
};

// End of the namespace gltut
}

#endif
