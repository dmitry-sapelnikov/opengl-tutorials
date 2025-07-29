// Includes
#include "FactoryC.h"

namespace gltut
{

// Constructor
FactoryC::FactoryC(Renderer& renderer, Scene& scene) noexcept :
	mGeometries(renderer),
	mMaterials(renderer, scene)
{
}

// Returns the geometry factory
GeometryFactory* FactoryC::getGeometries() noexcept
{
	return &mGeometries;
}

// Returns the material factory
MaterialFactory* FactoryC::getMaterials() noexcept
{
	return &mMaterials;
}

// End of the namespace gltut
}
