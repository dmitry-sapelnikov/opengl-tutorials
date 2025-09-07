#pragma once

// Includes
#include "engine/factory/material/FlatColorMaterialModel.h"
#include "engine/factory/material/MaterialFactory.h"
#include "./MaterialModelT.h"

namespace gltut
{
// Global classes

/// Implementation of the FlatColorMaterialModel interface
class FlatColorMaterialModelC final : public MaterialModelT<FlatColorMaterialModel>
{
public:
	FlatColorMaterialModelC(
		Renderer& renderer,
		ShaderRendererBinding& shader,
		ShaderRendererBinding* depthShader,
		ShaderUniformBuffer& viewProjectionBuffer);

	void setColor(const Texture* color) noexcept final;

	void setTransparencyThreshold(float threshold) noexcept final;
};

// End of the namespace gltut
}
