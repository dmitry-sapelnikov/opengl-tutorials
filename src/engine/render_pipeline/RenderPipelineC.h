#pragma once

// Includes
#include <vector>
#include <memory>

#include "engine/core/NonCopyable.h"
#include "engine/render_pipeline/RenderPipeline.h"
#include "engine/render_pipeline/passes/BasicRenderPass.h"
#include "engine/render_pipeline/passes/SceneRenderPass.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"

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

	/// Creates a basic render pass
	BasicRenderPass* createBasicPass(
		Framebuffer* target,
		const Color& clearColor = { 0.0f, 0.0f, 0.0f }) noexcept final;

	/// Creates a scene render pass
	SceneRenderPass* createScenePass(
		Framebuffer* target,
		const Viewpoint* viewer,
		u32 materialLayer,
		const Color& clearColor = { 0.0f, 0.0f, 0.0f }) noexcept final;

	/// Sets the priority of the render pass
	void setPassPriority(RenderPass* pass, int32 priority) noexcept final;

	/// Executes the render pipeline
	void execute() noexcept;

private:
	/// Renderer
	Renderer& mRenderer;

	/// Scene
	Scene& mScene;

	/// List of render passes
	std::vector<std::pair<std::unique_ptr<RenderPass>, u32>> mPasses;
};

// End of the namespace gltut
}
