// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

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
