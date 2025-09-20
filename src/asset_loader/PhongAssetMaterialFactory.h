#pragma once

// Includes
#include "asset_loader/AssetMaterialFactory.h"
#include "engine/core/NonCopyable.h"
#include "engine/factory/material/MaterialFactory.h"

namespace gltut
{
// Global classes
/// Phong asset material factory implementation
class PhongAssetMaterialFactory final : public AssetMaterialFactory, public NonCopyable
{
public:
	/// Constructor
	PhongAssetMaterialFactory(
		MaterialFactory& materialFactory,
		const PhongShaderModel& model,
		bool castShadows) noexcept :

		mMaterialFactory(materialFactory),
		mShaderModel(model),
		mCastShadows(castShadows)
	{
	}

	/// Creates a material using diffuse, specular and normal textures
	const Material* createMaterial(
		const Texture2* diffuseTexture,
		const Texture2* specularTexture,
		const Texture2* normalTexture) const noexcept final;

private:
	/// Reference to the material factory
	MaterialFactory& mMaterialFactory;

	/// Phong shader model
	const PhongShaderModel& mShaderModel;

	/// Whether the created materials should cast shadows
	bool mCastShadows;
};

// End of the namespace gltut
}
