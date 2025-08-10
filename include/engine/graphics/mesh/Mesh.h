#pragma once

// Includes
#include "engine/graphics/mesh/VertexFormat.h"

namespace gltut
{

/// The class represents a triangle mesh
class Mesh
{
public:
	/// Virtual destructor
	virtual ~Mesh() noexcept = default;

	/// Renders the mesh
	virtual void render() const noexcept = 0;
};

// End of the namespace gltut
}
