#pragma once

// Includes
#include "engine/factory/material/FlatColorMaterialModel.h"
#include "../MaterialModelT.h"

namespace gltut
{
// Global classes

/// Implementation of the PhongMaterialModel interface
class FlatColorMaterialModelC final : public MaterialModelT<FlatColorMaterialModel>
{
public:
	/// Constructor
	using MaterialModelT<FlatColorMaterialModel>::MaterialModelT;

	/// Sets the color texture
	void setColor(Texture* color) noexcept final
	{
		getMaterial()[0]->setTexture(color, 0);
	}
};

// End of the namespace gltut
}
