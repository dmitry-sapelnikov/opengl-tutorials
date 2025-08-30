#pragma once

// Includes
#include "RenderPassC.h"
#include "../objects/RenderGeometryGroupC.h"

namespace gltut
{
//	Global classes

///	Represents a render pass of the scene
class DepthSortedRenderPassC final : public RenderPassC
{
public:
	/// Constructor
	DepthSortedRenderPassC(
		const Viewpoint* viewpoint,
		const RenderGeometryGroup* group,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport,
		bool cullBackFaces,
		bool cullFrontFaces,
		GraphicsDevice& device,
		const ShaderBindings& shaderBindings) noexcept;

	/// Executes the render pass
	void execute() noexcept final;

private:
	const RenderGeometryGroup* mGroup;

	RenderGeometryGroupC mSortedGroup;

	Matrix4 mViewMatrix;
};

// End of the namespace gltut
}
