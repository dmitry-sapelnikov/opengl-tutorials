// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "SceneTextureSetBindingC.h"
#include "engine/scene/Scene.h"

namespace gltut
{
// Global classes
void SceneTextureSetBindingC::update(const Scene* scene) const noexcept
{
	u32 directionalInd = 0;
	u32 spotInd = 0;
	for (u32 lightInd = 0; lightInd < scene->getLightCount(); ++lightInd)
	{
		const auto* light = scene->getLight(lightInd);
		if (light == nullptr)
		{
			continue;
		}

		const Texture* shadowTexture = nullptr;
		if (light->getShadowMap() != nullptr &&
			light->getShadowMap()->getTexture() != nullptr)
		{
			shadowTexture = light->getShadowMap()->getTexture();
		}

		switch (light->getType())
		{
		case LightNode::Type::DIRECTIONAL:
		{
			if (const u32* startSlot = getStartTextureSlot(Parameter::DIRECTIONAL_LIGHT_SHADOW_MAP);
				startSlot != nullptr)
			{
				mTextureSet->setTexture(shadowTexture, *startSlot + directionalInd);
			}
			++directionalInd;
		}
		break;

		case LightNode::Type::SPOT:
		{
			if (const u32* startSlot = getStartTextureSlot(
					Parameter::SPOT_LIGHT_SHADOW_MAP);
				startSlot != nullptr)
			{
				mTextureSet->setTexture(shadowTexture, *startSlot + spotInd);
			}
			++spotInd;
			break;
		}

		case LightNode::Type::POINT:
			break;

			GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(light->getType())
		}
	}
}

// End of the namespace gltut
}
