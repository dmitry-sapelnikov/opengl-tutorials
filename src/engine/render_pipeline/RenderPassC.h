#pragma once

// Includes
#include <vector>
#include <optional>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/render_pipeline/RenderPass.h"
#include "engine/render_pipeline/viewpoint/ShaderViewpointBinding.h"

namespace gltut
{
//	Global classes

///	Represents a render pass of the scene
class RenderPassC final : public RenderPass, public NonCopyable
{
public:
	/// Vector of shader viewpoint bindings
	using ShaderViewpointBindings =
		std::vector<std::unique_ptr<ShaderViewpointBinding>>;

	/// Constructor
	RenderPassC(
		const Viewpoint* viewpoint,
		const RenderObject* object,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport,
		Renderer& renderer,
		const ShaderViewpointBindings& viewpointBindings) noexcept;

	/// Returns the scene viewpoint
	const Viewpoint* getViewpoint() const noexcept final
	{
		return mViewpoint;
	}

	/// Returns the object to render
	const RenderObject* getObject() const noexcept final
	{
		return mObject;
	}

	/// Returns the target frame buffer for this call
	Framebuffer* getTarget() const noexcept final
	{
		return mTarget;
	}

	/// Returns the material pass for this render pass
	u32 getMaterialPass() const noexcept final
	{
		return mMaterialPass;
	}

	/// Returns the clear color for the render target,
	/// nullptr if the buffer should not be cleared
	const Color* getClearColor() const noexcept final
	{
		return mClearColor.has_value() ? &mClearColor.value() : nullptr;
	}

	/// Returns if the depth clearing is enabled
	bool isDepthCleared() const noexcept final
	{
		return mClearDepth;
	}

	/// Returns the viewport rectangle for this render pass
	const Rectangle2u* getViewport() const noexcept final
	{
		return mViewport.has_value() ? &mViewport.value() : nullptr;
	}

	/// Executes the render pass
	void execute() noexcept final;

private:
	/// The viewpoint for this render pass
	const Viewpoint* mViewpoint;

	/// The object to render
	const RenderObject* mObject;

	/// The target frame buffer for this render pass
	Framebuffer* mTarget;

	/// The material pass for this render pass
	u32 mMaterialPass = 0;

	/// The clear color for the render target
	std::optional<Color> mClearColor;

	/// If the depth clearing is enabled
	bool mClearDepth = false;

	/// The viewport for this render pass
	std::optional<Rectangle2u> mViewport;

	/// Renderer
	Renderer& mRenderer;

	/// Viewpoint bindings
	const ShaderViewpointBindings& mViewpointBindings;
};

// End of the namespace gltut
}
