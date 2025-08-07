// Includes
#include "FactoryC.h"

namespace gltut
{

// Constructor
FactoryC::FactoryC(
	RenderPipeline& renderer,
	Scene& scene) noexcept :

	mGeometry(*renderer.getRenderer()),
	mMaterial(renderer, scene),
	mRenderPass(renderer, mGeometry)
{
}

// End of the namespace gltut
}
