// Includes
#include "PhongMaterialModelC.h"

namespace gltut
{
// Global classes
void PhongMaterialModelC::setDirectinalLightShadow(
	u32 lightIndex,
	const Viewpoint* shadowView,
	const Texture* shadowMap) noexcept
{
	auto* materialPass = getMaterial()[0];
	if (materialPass == nullptr)
	{
		return;
	}

	const u32 slot = 2 + lightIndex;
	if (shadowView == nullptr || shadowMap == nullptr)
	{
		mDirectionalLightShadows.erase(lightIndex);
		materialPass->setTexture(nullptr, slot);
	}
	else
	{
		mDirectionalLightShadows[lightIndex] = shadowView;
		materialPass->setTextureSlotsCount(
			std::max(slot + 1, materialPass->getTextureSlotsCount()));
		materialPass->setTexture(shadowMap, slot);
	}
}

void PhongMaterialModelC::update() noexcept
{
	for (const auto& [lightIndex, shadowView] : mDirectionalLightShadows)
	{
		const Matrix4 shadowMatrix =
			shadowView->getProjectionMatrix(1.0f) * shadowView->getViewMatrix();

		const std::string argumentName =
			"directionalLights[" + std::to_string(lightIndex) + "].shadowMatrix";

		getMaterial()[0]->getShaderArguments()->setMat4(
			argumentName.c_str(),
			shadowMatrix.data());
	}
}

// End of the namespace gltut
}
