// Includes
#include "FactoryC.h"

namespace gltut
{

// Constructor
FactoryC::FactoryC(
	Renderer& renderer,
	Scene& scene,
	Window& window) noexcept :

	mGeometry(*renderer.getDevice()),
	mMaterial(renderer, scene),
	mRenderPass(renderer),
	mShadow(renderer),
	mTexture(window)
{
}

// End of the namespace gltut
}
