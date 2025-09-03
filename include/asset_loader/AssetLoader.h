#pragma once

// Includes
#include "engine/Engine.h"
#include "asset_loader/AssetMaterialFactory.h"

namespace gltut
{
// Global classes
/// Loads assets from files
class AssetLoader
{
public:
	/// Virtual destructor
	virtual ~AssetLoader() noexcept = default;

	/**
		\brief Loads an asset (geometries, materials textures) from a file
		\return The scene node representing the asset if it was loaded successfully,
		nullptr otherwise
	*/
	virtual SceneNode* loadAsset(
		const char* filePath,
		const AssetMaterialFactory* materialCreator,
		bool loadTextures) noexcept = 0;
};

// Global functions
/// Creates an asset loader
AssetLoader* createAssetLoader(Engine* engine) noexcept;

/// Deletes an asset loader
void deleteAssetLoader(AssetLoader* factory) noexcept;

// End of the namespace gltut
}
