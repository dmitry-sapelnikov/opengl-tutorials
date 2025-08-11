// Includes
#include "ShadowMapC.h"

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
	u32 ShadowMapCSize) :

	mRenderer(renderer),
	mLight(light)
{
	GLTUT_CHECK(frustumSize > 0.0f, "Frustum size must be greater than 0.0f");
	GLTUT_CHECK(frustumNear > 0.0f, "Frustum near must be greater than 0.0f");
	GLTUT_CHECK(frustumFar > frustumNear, "Frustum far must be greater than frustum near");
	GLTUT_CHECK(ShadowMapCSize > 0, "Shadow map size must be greater than 0");

	mViewpoint.setProjectionMatrix(
		Matrix4::orthographicProjectionMatrix(
			frustumSize,
			frustumSize,
			frustumNear,
			frustumFar));

	mTexture = mRenderer.getDevice()->getTextures()->create(
		nullptr, // No data, we will render to it
		ShadowMapCSize,
		ShadowMapCSize,
		gltut::TextureFormat::FLOAT,
		{ gltut::TextureFilterMode::NEAREST,
		gltut::TextureFilterMode::NEAREST,
		gltut::TextureWrapMode::CLAMP_TO_EDGE });

	GLTUT_CHECK(mTexture != nullptr, "Failed to create depth texture");

	mFramebuffer = mRenderer.getDevice()->createTextureFramebuffer(
		nullptr,
		mTexture);
	GLTUT_CHECK(mFramebuffer, "Failed to create framebuffer");

	mRenderPass = mRenderer.createPass(
		&mViewpoint,
		&shadowCaster,
		mFramebuffer,
		0, // Material pass 0
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
	mRenderer.getDevice()->removeTextureFramebuffer(mFramebuffer);
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
}

// End of the namespace gltut
}
