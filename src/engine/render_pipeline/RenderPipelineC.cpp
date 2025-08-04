#pragma once

// Includes
#include "RenderPipelineC.h"
#include <algorithm>

namespace gltut
{
//	Global classes
RenderPipelineC::RenderPipelineC(
	Renderer& renderer,
	Scene& scene) :

	mRenderer(renderer),
	mScene(scene)
{
}

RenderPass* RenderPipelineC::createPass(
	Framebuffer* target,
	const Viewpoint* viewpoint,
	u32 materialLayer,
	const Color& clearColor) noexcept
{
	if (viewpoint == nullptr)
	{
		return nullptr;
	}
	RenderPass* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = mPasses.emplace_back(std::make_unique<RenderPassC>(
			mRenderer, mScene, target, viewpoint, clearColor, materialLayer)).get();
	GLTUT_CATCH_ALL_END("Cannot create a render pass")
	return result;
}

void RenderPipelineC::setPassPriority(u32 pass, int32 priority) noexcept
{
	if (pass >= mPasses.size())
	{
		return;
	}

	mPasses[pass]->setPriority(priority);
	std::sort(
		mPasses.begin(),
		mPasses.end(),
		[](const auto& a, const auto& b)
		{
			return a->getPriority() < b->getPriority();
		});
}

void RenderPipelineC::execute() noexcept
{
	for (const auto& pass : mPasses)
	{
		pass->execute();
	}
}

// End of the namespace gltut
}
