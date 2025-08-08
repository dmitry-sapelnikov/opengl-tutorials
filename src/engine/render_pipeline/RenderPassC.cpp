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
	Renderer& renderer,
	const ShaderViewpointBindings& viewpointBindings) noexcept :

	mViewpoint(viewpoint),
	mObject(object),
	mTarget(target),
	mMaterialPass(materialPass),
	mClearColor(clearColor ? std::make_optional(*clearColor) : std::nullopt),
	mClearDepth(clearDepth),
	mViewport(viewport ? std::make_optional(*viewport) : std::nullopt),
	mRenderer(renderer),
	mViewpointBindings(viewpointBindings)
{
}

void RenderPassC::execute() noexcept
{
	mRenderer.bindFramebuffer(
		mTarget, 
		mViewport.has_value() ? &mViewport.value() : nullptr);

	mRenderer.clear(
		mClearColor.has_value() ? &mClearColor.value() : nullptr,
		mClearDepth);

	const Point2u viewportSize = mViewport.has_value() ?
		mViewport->getSize() :
		mTarget->getSize();

	const float aspectRatio =
		viewportSize.x > 0 && viewportSize.y > 0 ?
		static_cast<float>(viewportSize.x) / static_cast<float>(viewportSize.y) :
		1.0f;

	for (const auto& binding : mViewpointBindings)
	{
		binding->update(mViewpoint, aspectRatio);
	}

	if (mObject != nullptr)
	{
		mObject->render(mMaterialPass);
	}
}

// End of the namespace gltut
}
