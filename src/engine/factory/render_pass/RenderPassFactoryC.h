#pragma once

// Includes
#include <array>
#include "engine/core/NonCopyable.h"
#include "engine/factory/render_pass/RenderPassFactory.h"
#include "engine/factory/geometry/GeometryFactory.h"

namespace gltut
{

class RenderPassFactoryC : public RenderPassFactory, public NonCopyable
{
public:
	/// Constructor
	RenderPassFactoryC(Renderer& renderer) noexcept :
		mRenderer(renderer)
	{
	}

	/// Creates a texture-to-window render pass
	RenderPass* createTextureToWindowRenderPass(
		const Texture* texture,
		const Rectangle2u& viewport) noexcept final;

private:
	/// The render pipeline
	Renderer& mRenderer;

	/// Depth texture shader
	std::array<ShaderMaterialBinding*, static_cast<size_t>(TextureFormat::TOTAL_COUNT)> mShaders;

	/// Render quad for the texture
	Geometry* mRenderQuad = nullptr;
};

// End of the namespace gltut
}
