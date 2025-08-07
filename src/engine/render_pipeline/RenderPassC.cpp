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
	mRenderer.activateFramebuffer(
		mTarget, 
		mViewport.has_value() ? &mViewport.value() : nullptr);

	mRenderer.clear(
		mClearColor.has_value() ? &mClearColor.value() : nullptr,
		mClearDepth);

	for (const auto& binding : mViewpointBindings)
	{
		binding->update(mViewpoint);
	}

	if (mObject != nullptr)
	{
		mObject->render(mMaterialPass);
	}
}

// End of the namespace gltut
}
