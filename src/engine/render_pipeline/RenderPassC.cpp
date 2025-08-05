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
	const Rectangle2u* viewport,
	Renderer& renderer,
	const ShaderViewpointBindings& viewpointBindings) noexcept :

	mViewpoint(viewpoint),
	mObject(object),
	mTarget(target),
	mMaterialPass(materialPass),
	mRenderer(renderer),
	mViewpointBindings(viewpointBindings)
{
	if (clearColor != nullptr)
	{
		mClearColor = *clearColor;
	}

	if (viewport != nullptr)
	{
		mViewport = *viewport;
	}
}

void RenderPassC::execute() noexcept
{
	mRenderer.activateFramebuffer(
		mTarget, 
		mViewport.has_value() ? &mViewport.value() : nullptr);

	if (mClearColor.has_value())
	{
		mRenderer.clear(*mClearColor);
	}

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
