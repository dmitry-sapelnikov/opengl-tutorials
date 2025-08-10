#pragma once

// Includes
#include <unordered_map>
#include "engine/factory/shadow/ShadowFactory.h"
#include "./ShadowMapC.h"


namespace gltut
{

class ShadowFactoryC : public ShadowFactory, public NonCopyable
{
public:
	/// Constructor
	ShadowFactoryC(Renderer& renderer) noexcept :
		mRenderer(renderer)
	{
	}

	/// Creates a shadow map for the given light
	ShadowMap* createShadowMap(
		const LightNode* light,
		const RenderObject* shadowCaster,
		float frustumSize,
		float frustumNear,
		float frustumFar,
		u32 shadowMapSize) noexcept final;

	/// Updates the shadow factory
	void update() noexcept final;

private:
	/// The device
	Renderer& mRenderer;

	/// The shadow maps
	std::unordered_map<const LightNode*, ShadowMapC> mShadowMaps;
};

// End of the namespace gltut
}
