#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/graphics/texture/Texture.h"
#include "engine/scene/nodes/LightNode.h"
#include "engine/factory/render_pass/RenderPassFactory.h"
#include "../../renderer/viewpoint/ViewpointC.h"

namespace gltut
{

class ShadowMapC : public ShadowMap, public NonCopyable
{
public:
	/// The priority of the shadow pass in the render pipeline
	static constexpr int32 SHADOW_PASS_PRIORITY = -1000;

	/**
		Constructor
		\throw std::runtime_error If the shadow map could not be created
	*/
	ShadowMapC(
		Renderer& renderer,
		const LightNode& light,
		const RenderObject& shadowCaster,
		float frustumSize,
		float frustumNear,
		float frustumFar,
		u32 textureSize);

	/// Destructor
	~ShadowMapC() noexcept;

	/// Returns the shadow map texture
	Texture* getTexture() const noexcept final
	{
		return mTexture;
	}

	/// Returns the viewpoint
	const Viewpoint* getViewpoint() const noexcept final
	{
		return &mViewpoint;
	}

	/// Returns the shadow matrix
	Matrix4 getShadowMatrix() const noexcept final
	{
		const float aspectRatio = mTexture != nullptr ?
			static_cast<float>(mTexture->getSize().x) / mTexture->getSize().y :
			1.0f;
		return mViewpoint.getProjectionMatrix(aspectRatio) * mViewpoint.getViewMatrix();
	}

	/// Updates the shadow map
	void update() noexcept final;

private:
	/// The device
	Renderer& mRenderer;

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
