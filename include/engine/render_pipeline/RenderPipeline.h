#pragma once

// Includes
#include "engine/render_pipeline/passes/BasicRenderPass.h"
#include "engine/render_pipeline/passes/SceneRenderPass.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RenderPipeline
{
public:
	/// Virtual destructor
	virtual ~RenderPipeline() noexcept = default;

	/// Creates a basic render pass
	virtual BasicRenderPass* createBasicPass(
		Framebuffer* target,
		const Color& clearColor = { 0.0f, 0.0f, 0.0f }) noexcept = 0;

	/// Creates a render pass
	virtual SceneRenderPass* createScenePass(
		Framebuffer* target,
		const Viewpoint* viewpoint,
		u32 materialLayer,
		const Color& clearColor = { 0.0f, 0.0f, 0.0f }) noexcept = 0;

	/// Sets the priority of the render pass
	virtual void setPassPriority(RenderPass* pass, int32 priority) noexcept = 0;
};

// End of the namespace gltut
}
