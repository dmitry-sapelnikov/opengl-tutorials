// Includes
#include "ShadowFactoryC.h"

namespace gltut
{

/// Creates a shadow map for the given light
std::pair<const Viewpoint*, const Texture*> ShadowFactoryC::createShadowMap(
	const LightNode* light,
	const RenderObject* shadowCaster,
	float frustumSize,
	float frustumNear,
	float frustumFar,
	u32 shadowMapSize) noexcept
{
	if (light == nullptr || shadowCaster == nullptr)
	{
		return { nullptr, nullptr };
	}

	// Currently only directional lights are supported
	if (light->getType() != LightNode::Type::DIRECTIONAL)
	{
		return { nullptr, nullptr };
	}

	ShadowMap* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		if (auto findResult = mShadowMaps.find(light);
			findResult != mShadowMaps.end())
		{
			result = &findResult->second;
		}
		else
		{
			// Create a new shadow map
			result = &mShadowMaps.try_emplace(
				light,
				mRenderer,
				*light,
				*shadowCaster,
				frustumSize,
				frustumNear,
				frustumFar,
				shadowMapSize).first->second;
		}
	GLTUT_CATCH_ALL_END("Failed to create shadow map for the light");
	
	return { &result->getViewpoint(), result->getTexture() };
}

/// Updates the shadow factory
void ShadowFactoryC::update() noexcept
{
	for (auto& [light, shadowMap] : mShadowMaps)
	{
		shadowMap.update();
	}
}

// End of the namespace gltut
}
