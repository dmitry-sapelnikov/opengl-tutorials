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
	mTexture(window),
	mScene(renderer, mGeometry)
{
}

// End of the namespace gltut
}
