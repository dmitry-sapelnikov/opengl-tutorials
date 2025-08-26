#pragma once

// Includes
#include "engine/Engine.h"

namespace gltut
{
// Global classes
/// Loads assets from files
class AssetLoader
{
public:
	/**
		\brief Loads an asset (geometries, materials textures) from a file
		\return The scene node representing the asset if it was loaded successfully,
		nullptr otherwise
	*/
	virtual SceneNode* loadAsset(
		const char* filePath,
		PhongShaderModel* phongShader) noexcept = 0;
};

AssetLoader* createAssetLoader(Engine* engine) noexcept;

void deleteAssetLoader(AssetLoader* factory) noexcept;

// End of the namespace gltut
}
