// Includes
#include "FactoryC.h"

namespace gltut
{

// Constructor
FactoryC::FactoryC(
	Renderer& renderer,
	Scene& scene) noexcept :

	mGeometry(*renderer.getDevice()),
	mMaterial(renderer, scene),
	mRenderPass(renderer),
	mShadow(renderer)
{
}

// End of the namespace gltut
}
