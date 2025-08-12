// Includes
#include "MaterialFactoryC.h"
#include "../shader/FlatColorShader.h"
#include "../shader/DepthShader.h"

namespace gltut
{

MaterialFactoryC::MaterialFactoryC(
	Renderer& renderer,
	Scene& scene) noexcept :

	mRenderer(renderer),
	mScene(scene)
{
}

FlatColorMaterialModel* MaterialFactoryC::createFlatColorMaterial(
	bool castShadows) noexcept
{
	FlatColorMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		createFlatColorShader();
		if (castShadows)
		{
			createDepthShader();
		}
		result = &mFlatColorModels.emplace_back(
			mRenderer,
			*mFlatColorShader,
			castShadows ? mDepthShader : nullptr);
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
	PhongShaderModel* phongShader,
	bool castShadows) noexcept
{
	if (phongShader == nullptr)
	{
		return nullptr;
	}

	PhongMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		if (castShadows)
		{
			createDepthShader();
		}
		result = &mPhongModels.emplace_back(
			mRenderer,
			mScene,
			*phongShader,
			castShadows ? mDepthShader : nullptr);
	GLTUT_CATCH_ALL_END("Cannot create a Phong material model")
	return result;
}

void MaterialFactoryC::createFlatColorShader()
{
	if (mFlatColorShader == nullptr)
	{
		mFlatColorShader = gltut::createFlatColorShader(mRenderer);
		GLTUT_CHECK(
			mFlatColorShader != nullptr,
			"Failed to create flat color shader");
	}
}

void MaterialFactoryC::createDepthShader()
{
	if (mDepthShader == nullptr)
	{
		mDepthShader = gltut::createDepthShader(mRenderer);
		GLTUT_CHECK(
			mDepthShader != nullptr,
			"Failed to create depth shader");
	}
}

void MaterialFactoryC::update() noexcept
{
}

// End of the namespace gltut
}
