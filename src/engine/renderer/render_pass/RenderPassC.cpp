// Includes
#include "RenderPassC.h"

namespace gltut
{
//	Global classes
RenderPassC::RenderPassC(
	const Viewpoint* viewpoint,
	const RenderObject* object,
	Framebuffer* target,
	u32 materialPass,
	const Color* clearColor,
	bool clearDepth,
	const Rectangle2u* viewport,
	bool cullBack,
	bool cullFront,
	bool enableBlending,
	GraphicsDevice& device,
	const ShaderBindings& shaderBindings) :

	mViewpoint(viewpoint),
	mObject(object),
	mTarget(target),
	mMaterialPass(materialPass),
	mClearColor(clearColor ? std::make_optional(*clearColor) : std::nullopt),
	mClearDepth(clearDepth),
	mViewport(viewport ? std::make_optional(*viewport) : std::nullopt),
	mCullBackFaces(cullBack),
	mCullFrontFaces(cullFront),
	mEnableBlending(enableBlending),
	mDevice(device),
	mShaderBindings(shaderBindings)
{
	GLTUT_CHECK(object != nullptr, "Object cannot be null");
	GLTUT_CHECK(target != nullptr, "Target framebuffer cannot be null");
}

void RenderPassC::execute() noexcept
{
	execute(mObject);
}

void RenderPassC::execute(const RenderObject* target) noexcept
{
	mDevice.setFaceCulling(
		mCullBackFaces,
		mCullFrontFaces);

	mDevice.bindFramebuffer(
		mTarget, 
		mViewport.has_value() ? &mViewport.value() : nullptr);

	mDevice.clear(
		mClearColor.has_value() ? &mClearColor.value() : nullptr,
		mClearDepth);

	mDevice.setBlending(mEnableBlending);

	const Point2u viewportSize = mViewport.has_value() ?
		mViewport->getSize() :
		mTarget->getSize();

	const float aspectRatio =
		viewportSize.x > 0 && viewportSize.y > 0 ?
		static_cast<float>(viewportSize.x) / static_cast<float>(viewportSize.y) :
		1.0f;

	for (const auto& binding : mShaderBindings)
	{
		binding->update(mViewpoint, aspectRatio);
	}

	if (target != nullptr)
	{
		target->render(mMaterialPass);
	}
}

// End of the namespace gltut
}
