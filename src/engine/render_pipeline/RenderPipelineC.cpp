#pragma once

// Includes
#include "RenderPipelineC.h"
#include <algorithm>
#include "./passes/BasicRenderPassC.h"
#include "./passes/SceneRenderPassC.h"

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

BasicRenderPass* RenderPipelineC::createBasicPass(
	Framebuffer* target,
	const Color& clearColor) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		auto resultPtr = std::make_unique<BasicRenderPassC>(
			mRenderer,
			target,
			clearColor);
	BasicRenderPass* result = resultPtr.get();
	mPasses.emplace_back(std::move(resultPtr), 0);
	return result;
	GLTUT_CATCH_ALL_END("Cannot create a basic render pass")
	return nullptr;
}

SceneRenderPass* RenderPipelineC::createScenePass(
	Framebuffer* target,
	const Viewpoint* viewpoint,
	u32 materialLayer,
	const Color& clearColor) noexcept
{
	if (viewpoint == nullptr)
	{
		return nullptr;
	}

	GLTUT_CATCH_ALL_BEGIN
		auto resultPtr = std::make_unique<SceneRenderPassC>(
			mRenderer,
			target,
			clearColor,
			mScene,
			viewpoint,
			materialLayer);
		SceneRenderPass* result = resultPtr.get();
		mPasses.emplace_back(std::move(resultPtr), 0);
		return result;
		GLTUT_CATCH_ALL_END("Cannot create a scene render pass")
	return nullptr;
}

void RenderPipelineC::setPassPriority(RenderPass* pass, int32 priority) noexcept
{
	auto findResult = std::find_if(
		mPasses.begin(),
		mPasses.end(),
		[&pass](const auto& currentPass)
		{
			return currentPass.first.get() == pass;
		});

	if (findResult != mPasses.end())
	{
		findResult->second = priority;
		std::sort(
			mPasses.begin(),
			mPasses.end(),
			[](const auto& pass1, const auto& pass2)
			{
				return pass1.second < pass2.second;
			});
	}
}

void RenderPipelineC::execute() noexcept
{
	for (const auto& pass : mPasses)
	{
		pass.first->execute();
	}
}

// End of the namespace gltut
}
