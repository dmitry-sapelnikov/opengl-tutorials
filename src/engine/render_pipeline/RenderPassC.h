#pragma once

// Includes
#include <vector>
#include <memory>
#include "engine/core/NonCopyable.h"

#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"
#include "engine/render_pipeline/RenderPass.h"
#include "../scene/shader/SceneShaderBindingC.h"
#include "../scene/material/MaterialC.h"

namespace gltut
{
//	Global classes

///	Represents a render pass of the scene
class RenderPassC final : public RenderPass, public NonCopyable
{
public:
	/// Constructor
	RenderPassC(
		Renderer& renderer,
		Scene& scene,
		Framebuffer* target,
		const Viewpoint* viewpoint,
		const Color& clearColor,
		u32 materialPass) noexcept;

	/// Returns the target frame buffer for this call
	Framebuffer* getTarget() const noexcept final
	{
		return mTarget;
	}

	/// Returns the view projection matrices for this call
	const Viewpoint* getViewpoint() const noexcept final
	{
		return mViewpoint;
	}

	/// Returns the clear color for the render target
	const Color& getClearColor() const noexcept final
	{
		return mClearColor;
	}

	/// Sets the clear color for the render target
	void setClearColor(const Color& color) noexcept final
	{
		mClearColor = color;
	}

	/// Returns the material pass for this render pass
	u32 getMaterialPass() const noexcept final
	{
		return mMaterialPass;
	}

	/// Sets the material pass for this render pass
	void setMaterialPass(u32 pass) noexcept final
	{
		mMaterialPass = pass;
	}

	/// Executes the render pass
	void execute() noexcept final;

	/// Returns the priority of this render pass
	int32 getPriority() const noexcept
	{
		return mPriority;
	}

	/// Sets the priority of this render pass
	void setPriority(int32 priority) noexcept
	{
		mPriority = priority;
	}

private:
	/// The renderer for this render pass call
	Renderer& mRenderer;

	/// The scene for this render pass call
	Scene& mScene;

	/// The target frame buffer for this render pass
	Framebuffer* mTarget;

	/// The viewpoint for this render pass
	const Viewpoint* mViewpoint;

	/// The clear color for the render target
	Color mClearColor;

	/// The material pass for this render pass
	u32 mMaterialPass = 0;

	/// Priority
	int32 mPriority = 0;
};

// End of the namespace gltut
}
