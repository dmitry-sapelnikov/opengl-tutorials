#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/graphics/Texture.h"
#include "engine/scene/nodes/LightNode.h"
#include "engine/factory/render_pass/RenderPassFactory.h"
#include "../../render_pipeline/viewpoint/ViewpointC.h"

namespace gltut
{

class ShadowMap : public NonCopyable
{
public:
	/// The priority of the shadow pass in the render pipeline
	static constexpr int32 SHADOW_PASS_PRIORITY = -1000;

	/**
		Constructor
		\throw std::runtime_error If the shadow map could not be created
	*/
	ShadowMap(
		RenderPipeline& renderer,
		const LightNode& light,
		const RenderObject& shadowCaster,
		float frustumSize,
		float frustumNear,
		float frustumFar,
		u32 shadowMapSize);

	/// Destructor
	~ShadowMap() noexcept;

	/// Returns the shadow map texture
	Texture* getTexture() const noexcept
	{
		return mTexture;
	}

	/// Returns the viewpoint
	const Viewpoint& getViewpoint() noexcept
	{
		return mViewpoint;
	}

	/// Updates the shadow map
	void update() noexcept;

private:
	/// The device
	RenderPipeline& mRenderer;

	/// The light node for which the shadow map is created
	const LightNode& mLight;

	/// The shadow map texture
	Texture* mTexture = nullptr;

	/// The shadow map framebuffer
	gltut::TextureFramebuffer* mFramebuffer = nullptr;

	/// The render pass for the shadow map
	RenderPass* mRenderPass = nullptr;

	/// The viewpoint for the shadow map
	ViewpointC mViewpoint;
};

// End of the namespace gltut
}
