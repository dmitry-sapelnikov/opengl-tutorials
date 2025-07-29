#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/Factory.h"

#include "./geometry/GeometryFactoryC.h"
#include "./material/MaterialFactoryC.h"

namespace gltut
{

/// Implementation of the Factory interface
class FactoryC final : public Factory, public NonCopyable
{
public:
	// Constructor
	explicit FactoryC(Renderer& renderer, Scene& scene) noexcept;

	// Returns the geometry factory
	GeometryFactory* getGeometry() noexcept final;

	// Returns the material factory
	MaterialFactory* getMaterial() noexcept final;

private:
	/// The geometry factory
	GeometryFactoryC mGeometries;

	/// The material factory
	MaterialFactoryC mMaterials;
};

// End of the namespace gltut
}
