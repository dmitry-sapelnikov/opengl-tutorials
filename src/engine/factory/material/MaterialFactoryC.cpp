// Includes
#include "MaterialFactoryC.h"
#include "./phong/PhongShader.h"

namespace gltut
{

MaterialFactoryC::MaterialFactoryC(Renderer& renderer, Scene& scene) noexcept :
	mRenderer(renderer),
	mScene(scene)
{
}

/// Creates a Phong shader
SceneShaderBinding* MaterialFactoryC::createPhongShader(
	Renderer* renderer,
	Scene* scene,
	u32 maxDirectionalLights,
	u32 maxPointLights,
	u32 maxSpotLights) noexcept
{
	if (renderer == nullptr || scene == nullptr)
	{
		return nullptr;
	}

	SceneShaderBinding* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		const auto lightCounts = std::make_tuple(
			maxDirectionalLights,
			maxPointLights,
			maxSpotLights);

		if (auto findResult = mPhongShaders.find(lightCounts);
			findResult != mPhongShaders.end())
		{
			result = findResult->second;
		}
		else
		{
			result = gltut::createPhongShader(
				*renderer,
				*scene,
				maxDirectionalLights,
				maxPointLights,
				maxSpotLights);
			if (result != nullptr)
			{
				mPhongShaders[lightCounts] = result;
			}
		}
	GLTUT_CATCH_ALL_END("Cannot create a Phong shader")
	return result;
}

PhongMaterialModel* MaterialFactoryC::createPhongMaterial(SceneShaderBinding* phongShader) noexcept
{
	Material* material = mScene.createMaterial(phongShader);
	if (material == nullptr)
	{
		return nullptr;
	}

	PhongMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mPhongModels.emplace_back(*material);
	GLTUT_CATCH_ALL_END("Cannot create a Phong material model")
	return result;
}

// End of the namespace gltut
}
