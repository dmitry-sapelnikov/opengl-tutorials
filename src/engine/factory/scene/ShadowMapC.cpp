// Includes
#include "ShadowMapC.h"
#include "engine/factory/material/MaterialPassIndex.h"

namespace gltut
{
// Global classes
ShadowMapC::ShadowMapC(
	Renderer& renderer,
	const LightNode& light,
	const RenderObject& shadowCaster,
	float frustumSize,
	float frustumNear,
	float frustumFar,
	u32 textureSize) :

	ShadowMapC(
		0,
		renderer,
		light,
		shadowCaster,
		frustumNear,
		frustumFar,
		textureSize)
{
	GLTUT_CHECK(
		light.getType() == LightNode::Type::DIRECTIONAL,
		"Invalid light type for this contructor");
	GLTUT_CHECK(frustumSize > 0.0f, "Frustum size must be greater than 0.0f");
	GLTUT_CHECK(textureSize > 0, "Shadow map texture size must be greater than 0");

	mViewpoint.setProjectionMatrix(
		Matrix4::orthographicProjectionMatrix(
			frustumSize,
			frustumSize,
			frustumNear,
			frustumFar));
}


ShadowMapC::ShadowMapC(
	Renderer& renderer,
	const LightNode& light,
	const RenderObject& shadowCaster,
	float frustumNear,
	float frustumFar,
	u32 textureSize) :

	ShadowMapC(
		0,
		renderer,
		light,
		shadowCaster,
		frustumNear,
		frustumFar,
		textureSize)
{
	GLTUT_CHECK(
		light.getType() == LightNode::Type::SPOT,
		"Invalid light type for this contructor");
}

ShadowMapC::ShadowMapC(
	u32,
	Renderer& renderer,
	const LightNode& light,
	const RenderObject& shadowCaster,
	float frustumNear,
	float frustumFar,
	u32 textureSize) :
	mRenderer(renderer),
	mLight(light),
	mFrustumNear(frustumNear),
	mFrustumFar(frustumFar)
{
	GLTUT_CHECK(
		light.getType() == LightNode::Type::DIRECTIONAL ||
		light.getType() == LightNode::Type::SPOT,
		"Invalid light type for this contructor");

	GLTUT_CHECK(mFrustumNear > 0.0f, "Frustum near must be greater than 0.0f");
	GLTUT_CHECK(mFrustumFar > mFrustumNear, "Frustum far must be greater than frustum near");

	mTexture = mRenderer.getDevice()->getTextures()->create(
		{ nullptr, // No data, we will render to it
		{ textureSize, textureSize },
		gltut::TextureFormat::FLOAT },
		{ gltut::TextureFilterMode::NEAREST,
		gltut::TextureFilterMode::NEAREST,
		gltut::TextureWrapMode::CLAMP_TO_EDGE });

	GLTUT_CHECK(mTexture != nullptr, "Failed to create depth texture");

	mFramebuffer = mRenderer.getDevice()->getFramebuffers()->create(
		nullptr,
		mTexture);
	GLTUT_CHECK(mFramebuffer, "Failed to create framebuffer");

	mRenderPass = mRenderer.createPass(
		&mViewpoint,
		&shadowCaster,
		mFramebuffer,
		static_cast<u32>(MaterialPassIndex::DEPTH),
		nullptr, // No clear color
		true, // Depth clearing
		nullptr);

	GLTUT_CHECK(mRenderPass != nullptr, "Failed to create shadow map render pass");
	mRenderer.setPassPriority(mRenderPass, SHADOW_PASS_PRIORITY);
	update();
}

ShadowMapC::~ShadowMapC() noexcept
{
	mRenderer.removePass(mRenderPass);
	mRenderer.getDevice()->getFramebuffers()->remove(mFramebuffer);
	mRenderer.getDevice()->getTextures()->remove(mTexture);
}

void ShadowMapC::update() noexcept
{
	const Vector3 position = mLight.getGlobalTransform().getTranslation();
	const Vector3 target = position + mLight.getGlobalDirection();

	mViewpoint.setPosition(position);
	mViewpoint.setViewMatrix(
		Matrix4::lookAtMatrix(
			position,
			target,
			Vector3(0.0f, 1.0f, 0.0f)));

	if (mLight.getType() == LightNode::Type::SPOT)
	{
		const float aspectRatio = mTexture != nullptr ?
			mTexture->getAspectRatio() :
			1.0f;

		mViewpoint.setProjectionMatrix(
			Matrix4::perspectiveProjectionMatrix(
				mLight.getOuterAngle() * 2.0f,
				aspectRatio,
				mFrustumNear,
				mFrustumFar));
	}
}

// End of the namespace gltut
}
