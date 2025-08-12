#pragma once

// Includes
#include "engine/factory/material/FlatColorMaterialModel.h"
#include "engine/factory/material/MaterialFactory.h"
#include "./MaterialModelT.h"

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
		ShaderRendererBinding& shader,
		ShaderRendererBinding* depthShader);

	/// Sets the color texture
	void setColor(const Texture* color) noexcept final;
};

// End of the namespace gltut
}
