// Includes
#include "FactoryC.h"

namespace gltut
{

// Constructor
FactoryC::FactoryC(
	RenderPipeline& renderer,
	Scene& scene) noexcept :

	mGeometries(*renderer.getRenderer()),
	mMaterials(renderer, scene)
{
}

// Returns the geometry factory
GeometryFactory* FactoryC::getGeometry() noexcept
{
	return &mGeometries;
}

// Returns the material factory
MaterialFactory* FactoryC::getMaterial() noexcept
{
	return &mMaterials;
}

// End of the namespace gltut
}
