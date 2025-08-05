// Includes
#include "MaterialFactoryC.h"
#include "./phong/PhongShader.h"
#include "./flat_color//FlatColorShader.h"

namespace gltut
{

MaterialFactoryC::MaterialFactoryC(
	RenderPipeline& renderer,
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

	Material* material = mRenderer.createMaterial();
	if (material == nullptr)
	{
		return nullptr;
	}

	if (auto* pass = material->createPass(0, mFlatColorShader, 1);
		pass == nullptr)
	{
		mRenderer.removeMaterial(material);
		return nullptr;
	}

	FlatColorMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mFlatColorModels.emplace_back(*material);
	GLTUT_CATCH_ALL_END("Cannot create a flat color material model")

		if (result == nullptr)
		{
			mRenderer.removeMaterial(material);
		}
	return result;
}

ShaderMaterialBinding* MaterialFactoryC::createPhongShader(
	u32 maxDirectionalLights,
	u32 maxPointLights,
	u32 maxSpotLights) noexcept
{
	ShaderMaterialBinding* result = nullptr;
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
				mRenderer,
				mScene,
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

PhongMaterialModel* MaterialFactoryC::createPhongMaterial(
	ShaderMaterialBinding* phongShader) noexcept
{
	Material* material = mRenderer.createMaterial();
	if (material == nullptr)
	{
		return nullptr;
	}

	if (auto* pass = material->createPass(0, phongShader, 3);
		pass == nullptr)
	{
		mRenderer.removeMaterial(material);
		return nullptr;
	}

	PhongMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mPhongModels.emplace_back(*material);
	GLTUT_CATCH_ALL_END("Cannot create a Phong material model")

		if (result == nullptr)
		{
			mRenderer.removeMaterial(material);
		}
	return result;
}

// End of the namespace gltut
}
