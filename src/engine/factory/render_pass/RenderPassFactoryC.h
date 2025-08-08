#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/render_pass/RenderPassFactory.h"
#include "engine/factory/geometry/GeometryFactory.h"

namespace gltut
{

class RenderPassFactoryC : public RenderPassFactory, public NonCopyable
{
public:
	/// Constructor
	RenderPassFactoryC(
		RenderPipeline& renderer,
		GeometryFactory& geometryFactory) noexcept :
		mRenderer(renderer),
		mGeometryFactory(geometryFactory)
	{
	}

	/// Creates a texture-to-window render pass
	RenderPass* createTextureToWindowRenderPass(
		const Texture* texture,
		const Rectangle2u& viewport) noexcept final;

private:
	/// The render pipeline
	RenderPipeline& mRenderer;

	/// The geometry factory
	GeometryFactory& mGeometryFactory;

	/// The texture-to-window shader
	ShaderMaterialBinding* mTextureToWindowShader = nullptr;

	/// Render quad for the texture
	Mesh* mRenderQuad = nullptr;
};

// End of the namespace gltut
}
