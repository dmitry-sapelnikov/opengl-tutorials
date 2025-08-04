#pragma once

// Includes
#include <vector>
#include <memory>

#include "engine/core/NonCopyable.h"
#include "engine/render_pipeline/RenderPipeline.h"
#include "./RenderPassC.h"
#include "engine/window/EventHandler.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RenderPipelineC final : public RenderPipeline, public NonCopyable
{
public:
	/// Constructor
	RenderPipelineC(
		Renderer& renderer,
		Scene& scene);

	/// Creates a render pass
	RenderPass* createPass(
		Framebuffer* target,
		const Viewpoint* viewer,
		u32 materialLayer,
		const Color& clearColor = { 0.0f, 0.0f, 0.0f }) noexcept final;

	/// Returns the number of render passes
	u32 getPassCount() const noexcept final
	{
		return static_cast<u32>(mPasses.size());
	}

	/// Returns the render pass at the specified index
	RenderPass* getPass(u32 index) noexcept final
	{
		return mPasses[index].get();
	}

	/// Sets the priority of the render pass
	void setPassPriority(u32 index, int32 priority) noexcept final;

	/// Executes the render pipeline
	void execute() noexcept;

private:
	/// Renderer
	Renderer& mRenderer;

	/// Scene
	Scene& mScene;

	/// List of render passes
	std::vector<std::unique_ptr<RenderPassC>> mPasses;
};

// End of the namespace gltut
}
