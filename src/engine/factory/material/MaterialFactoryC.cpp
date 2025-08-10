// Includes
#include "MaterialFactoryC.h"
#include "./flat_color/FlatColorShader.h"

namespace gltut
{

MaterialFactoryC::MaterialFactoryC(
	Renderer& renderer,
	Scene& scene) noexcept :

	mRenderer(renderer),
	mScene(scene)
{
}

FlatColorMaterialModel* MaterialFactoryC::createFlatColorMaterial() noexcept
{
	if (mFlatColorShader == nullptr)
	{
		mFlatColorShader = gltut::createFlatColorShader(mRenderer);
		if (mFlatColorShader == nullptr)
		{
			return nullptr;
		}
	}

	FlatColorMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mFlatColorModels.emplace_back(mRenderer, *mFlatColorShader);
	GLTUT_CATCH_ALL_END("Cannot create a flat color material model")
	return result;
}

PhongShaderModel* MaterialFactoryC::createPhongShader(
	u32 maxDirectionalLights,
	u32 maxPointLights,
	u32 maxSpotLights) noexcept
{
	PhongShaderModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		const auto lightCounts = std::make_tuple(
			maxDirectionalLights,
			maxPointLights,
			maxSpotLights);

		if (auto findResult = mPhongShaders.find(lightCounts);
			findResult != mPhongShaders.end())
		{
			result = &findResult->second;
		}
		else
		{
			result = &mPhongShaders.try_emplace(
				lightCounts,
				mRenderer,
				mScene,
				maxDirectionalLights,
				maxPointLights,
				maxSpotLights).first->second;
		}
	GLTUT_CATCH_ALL_END("Cannot create a Phong shader")
	return result;
}

PhongMaterialModel* MaterialFactoryC::createPhongMaterial(
	PhongShaderModel* phongShader) noexcept
{
	if (phongShader == nullptr)
	{
		return nullptr;
	}

	PhongMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mPhongModels.emplace_back(
			mRenderer,
			mScene,
			*phongShader);
	GLTUT_CATCH_ALL_END("Cannot create a Phong material model")
	return result;
}

void MaterialFactoryC::update() noexcept
{
}

// End of the namespace gltut
}
