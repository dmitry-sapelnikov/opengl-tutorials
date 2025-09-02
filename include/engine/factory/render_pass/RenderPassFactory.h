#pragma once

// Includes
#include "engine/renderer/Renderer.h"

namespace gltut
{

class RenderPassFactory
{
public:
	/// Virtual destructor
	virtual ~RenderPassFactory() noexcept = default;

	/// Creates a texture-to-window render pass
	virtual RenderPass* createTextureToWindowRenderPass(
		const Texture2* texture,
		const Rectangle2u* viewport) noexcept = 0;

	/// Creates a textures-to-window render pass
	virtual RenderPass* createTexturesToWindowRenderPass(
		const Texture2** textures,
		u32 textureCount,
		const Rectangle2u* viewport,
		const char* fragmentShader,
		const char** textureSamplerNames) noexcept = 0;
};

// End of the namespace gltut
}
