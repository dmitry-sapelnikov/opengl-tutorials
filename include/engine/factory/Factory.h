#pragma once

// Includes
#include "engine/factory/geometry/GeometryFactory.h"
#include "engine/factory/material/MaterialFactory.h"

namespace gltut
{
// Global classes
/// The factory interface. Creates various elements used in the engine.
class Factory
{
public:
	/// Returns the geometry factory
	virtual GeometryFactory* getGeometries() noexcept = 0;

	/// Returns the material factory
	virtual MaterialFactory* getMaterials() noexcept = 0;
};

// End of the namespace gltut
}
