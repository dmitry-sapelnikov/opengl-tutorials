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

PhongMaterialModel* MaterialFactoryC::createPhongModel() noexcept
{
	// Create the Phong shader if it does not exist
	if (mPhongShader == nullptr)
	{
		mPhongShader = createPhongShader(mRenderer, mScene);
		if (mPhongShader == nullptr)
		{
			return nullptr;
		}
	}

	Material* material = mScene.createMaterial(mPhongShader);
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
