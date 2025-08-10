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
	FlatColorMaterialModelC(
		Renderer& renderer,
		ShaderMaterialBinding& shader) :
		MaterialModelT<FlatColorMaterialModel>(renderer)
	{
		// Create a material pass with the flat color shader binding
		auto* materialPass = getMaterial().createPass(0, &shader, 1);
		GLTUT_CHECK(materialPass != nullptr, "Failed to create a material pass");
	}

	/// Sets the color texture
	void setColor(Texture* color) noexcept final
	{
		getMaterial()[0]->getTextures()->setTexture(color, 0);
	}
};

// End of the namespace gltut
}
