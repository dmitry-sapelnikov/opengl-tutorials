#pragma once

// Includes
#include "RenderPassC.h"
#include "engine/renderer/objects/RenderGroup.h"

namespace gltut
{
//	Global classes

///	Represents a render pass of the scene
class DepthSortedRenderPassC final : public RenderPassC
{
public:
	/// Vector of shader viewpoint bindings
	using ShaderBindings =
		std::vector<std::unique_ptr<ShaderRendererBinding>>;

	/// Constructor
	DepthSortedRenderPassC(
		const Viewpoint* viewpoint,
		RenderGroup* group,
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
	RenderGroup* mGroup;

	Matrix4 mViewpointMatrix;
};

// End of the namespace gltut
}
