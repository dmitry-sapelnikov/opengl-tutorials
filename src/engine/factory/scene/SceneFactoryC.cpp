// Includes
#include "SceneFactoryC.h"

namespace gltut
{

/// Creates a shadow map for the given light
ShadowMap* SceneFactoryC::createShadowMap(
	const LightNode* light,
	const RenderObject* shadowCaster,
	float frustumSize,
	float frustumNear,
	float frustumFar,
	u32 shadowMapSize) noexcept
{
	if (light == nullptr || shadowCaster == nullptr ||
		light->getType() == LightNode::Type::POINT)
	{
		return nullptr;
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
			switch (light->getType())
			{
			case LightNode::Type::DIRECTIONAL:
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
				break;

				case LightNode::Type::SPOT:
				{
					result = &mShadowMaps.try_emplace(
						light,
						mRenderer,
						*light,
						*shadowCaster,
						frustumNear,
						frustumFar,
						shadowMapSize).first->second;
				}
				break;

				GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(light->getType())
			}
		}
	GLTUT_CATCH_ALL_END("Failed to create shadow map for the light");
	return result;
}

/// Updates the shadow factory
void SceneFactoryC::update() noexcept
{
	for (auto& [light, shadowMap] : mShadowMaps)
	{
		shadowMap.update();
	}
}

// End of the namespace gltut
}
