#pragma once

// Includes
#include "engine/graphics/geometry/VertexFormat.h"

namespace gltut
{

/// The class represents a geometry to render
class Geometry
{
public:
	/// Virtual destructor
	virtual ~Geometry() noexcept = default;

	/// Renders the geometry
	virtual void render() const noexcept = 0;
};

// End of the namespace gltut
}
