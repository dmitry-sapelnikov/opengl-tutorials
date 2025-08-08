#pragma once

// Includes
#include "engine/render_pipeline/RenderPipeline.h"

namespace gltut
{

class RenderPassFactory
{
public:
	/// Virtual destructor
	virtual ~RenderPassFactory() noexcept = default;

	/// Creates a texture-to-window render pass
	virtual RenderPass* createTextureToWindowRenderPass(
		const Texture* texture,
		const Rectangle2u& viewport) noexcept = 0;
};

// End of the namespace gltut
}
