#pragma once

// Includes
#include <unordered_map>
#include "engine/factory/scene/SceneFactory.h"
#include "./ShadowMapC.h"


namespace gltut
{

class SceneFactoryC : public SceneFactory, public NonCopyable
{
public:
	/// Constructor
	SceneFactoryC(Renderer& renderer) noexcept :
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
