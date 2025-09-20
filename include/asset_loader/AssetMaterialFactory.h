#pragma once

// Includes
#include "engine/factory/material/MaterialFactory.h"

namespace gltut
{
// Global classes
/// Asset material creation interface
class AssetMaterialFactory
{
public:
	/// Virtual destructor
	virtual ~AssetMaterialFactory() noexcept = default;

	/// Creates a material using diffuse, specular and normal textures
	virtual const Material* createMaterial(
		const Texture2* diffuseTexture,
		const Texture2* specularTexture,
		const Texture2* normalTexture) const noexcept = 0;
};

// Global functions
/// Creates a Phong asset material factory
AssetMaterialFactory* createPhongAssetMaterialFactory(
	MaterialFactory* materialFactory,
	const PhongShaderModel* shaderModel,
	bool castShadows) noexcept;

/// Deletes a material factory
void deleteAssetMaterialFactory(AssetMaterialFactory* factory) noexcept;

// End of the namespace gltut
}
