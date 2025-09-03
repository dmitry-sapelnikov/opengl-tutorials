// Includes
#include "PhongAssetMaterialFactory.h"

namespace gltut
{
// Global classes
const Material* PhongAssetMaterialFactory::createMaterial(
	const Texture2* diffuseTexture,
	const Texture2* specularTexture,
	const Texture2* normalTexture) const noexcept
{
	const Material* result = nullptr;
	try
	{
		PhongMaterialModel* material = mMaterialFactory.createPhongMaterial(&mShaderModel, mCastShadows);
		GLTUT_CHECK(material != nullptr, "Failed to create a Phong material model");

		material->setDiffuse(diffuseTexture);
		material->setSpecular(specularTexture);
		material->setNormal(normalTexture);

		result = material->getMaterial();
	}
	GLTUT_CATCH_ALL("Failed to create a Phong material")
	return result;
}

// Global functions
AssetMaterialFactory* createPhongAssetMaterialFactory(
	MaterialFactory* materialFactory,
	const PhongShaderModel* shaderModel,
	bool castShadows) noexcept
{
	AssetMaterialFactory* result = nullptr;
	try
	{
		GLTUT_CHECK(materialFactory != nullptr, "Material factory cannot be null");
		GLTUT_CHECK(shaderModel != nullptr, "Shader model cannot be null");
		result = new PhongAssetMaterialFactory(
			*materialFactory,
			*shaderModel,
			castShadows);
	}
	GLTUT_CATCH_ALL("Failed to create PhongAssetMaterialFactory")
	return result;
}

// End of the namespace gltut
}
