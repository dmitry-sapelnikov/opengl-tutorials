// Includes
#include "SceneTextureSetBindingC.h"
#include "engine/scene/Scene.h"

namespace gltut
{

void SceneTextureSetBindingC::update(const Scene* scene) const noexcept
{
	u32 directionalInd = 0;
	for (u32 lightInd = 0; lightInd < scene->getLightCount(); ++lightInd)
	{
		if (const auto* light = scene->getLight(lightInd);
			light->getType() == LightNode::Type::DIRECTIONAL)
		{
			if (const u32* startSlot = getStartTextureSlot(Parameter::DIRECTIONAL_LIGHT_SHADOW_MAP);
				startSlot != nullptr)
			{
				const Texture* texture = nullptr;
				if (light->getShadowMap() != nullptr &&
					light->getShadowMap()->getTexture() != nullptr)
				{
					texture = light->getShadowMap()->getTexture();
				}
				mTextureSet->setTexture(texture, *startSlot + directionalInd);
			}
			++directionalInd;
		}
	}
}

// End of the namespace gltut
}
