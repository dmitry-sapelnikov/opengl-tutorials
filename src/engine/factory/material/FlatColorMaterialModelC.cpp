// Includes
#include "FlatColorMaterialModelC.h"
#include "engine/factory/material/MaterialPassIndex.h"

namespace gltut
{
// Global classes
FlatColorMaterialModelC::FlatColorMaterialModelC(
	Renderer& renderer,
	ShaderRendererBinding& shader,
	ShaderRendererBinding* depthShader) :
	MaterialModelT<FlatColorMaterialModel>(renderer)
{
	// Create a material pass with the flat color shader binding
	auto* colorPass = getMaterial().createPass(
		static_cast<u32>(MaterialPassIndex::LIGHTING),
		&shader,
		1);

	GLTUT_CHECK(colorPass != nullptr, "Failed to create a material pass");

	if (depthShader != nullptr)
	{
		// Create a depth pass if the depth shader is provided
		auto* depthPass = getMaterial().createPass(
			static_cast<u32>(MaterialPassIndex::DEPTH),
			depthShader,
			0);
		GLTUT_CHECK(depthPass != nullptr, "Failed to create a depth pass");
	}
}

void FlatColorMaterialModelC::setColor(const Texture* color) noexcept
{
	MaterialPass* pass = getMaterial()[static_cast<u32>(MaterialPassIndex::LIGHTING)];
	GLTUT_ASSERT(pass != nullptr);
	if (pass != nullptr)
	{
		pass->getTextures()->setTexture(color, 0);
	}
}

void FlatColorMaterialModelC::setTransparencyThreshold(float threshold) noexcept
{
	const bool thresholdInRange = 0.0f <= threshold && threshold <= 1.0f;
	GLTUT_ASSERT(thresholdInRange);

	MaterialPass* pass = getMaterial()[static_cast<u32>(MaterialPassIndex::LIGHTING)];
	GLTUT_ASSERT(pass != nullptr);

	if (thresholdInRange && pass != nullptr)
	{
		pass->getShader()->getShader()->setFloat("transparencyThreshold", threshold);
	}
}

// End of the namespace gltut
}
