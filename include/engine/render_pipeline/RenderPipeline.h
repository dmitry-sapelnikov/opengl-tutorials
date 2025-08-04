#pragma once

// Includes
#include "engine/render_pipeline/RenderPass.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RenderPipeline
{
public:
	/// Virtual destructor
	virtual ~RenderPipeline() noexcept = default;

	/// Creates a render pass
	virtual RenderPass* createPass(
		Framebuffer* target,
		const Viewpoint* viewpoint,
		u32 materialLayer,
		const Color& clearColor = { 0.0f, 0.0f, 0.0f }) noexcept = 0;

	/// Returns the number of render passes
	virtual u32 getPassCount() const noexcept = 0;

	/// Returns the render pass at the specified index
	virtual RenderPass* getPass(u32 index) noexcept = 0;

	/// Sets the priority of the render pass
	virtual void setPassPriority(u32 index, int32 priority) noexcept = 0;
};

// End of the namespace gltut
}
