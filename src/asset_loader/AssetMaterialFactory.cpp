#pragma once

// Includes
#include "asset_loader/AssetMaterialFactory.h"

namespace gltut
{

// Global functions
void deleteAssetMaterialFactory(AssetMaterialFactory* factory) noexcept
{
	delete factory;
}

// End of the namespace gltut
}
