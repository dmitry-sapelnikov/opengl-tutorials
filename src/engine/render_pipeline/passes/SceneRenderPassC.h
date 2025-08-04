#pragma once

// Includes
#include <vector>
#include "engine/render_pipeline/passes/SceneRenderPass.h"
#include "engine/scene/Scene.h"
#include "./RenderPassT.h"

namespace gltut
{
//	Global classes

///	Represents a render pass of the scene
class SceneRenderPassC final : public RenderPassT<SceneRenderPass>
{
public:
	/// Constructor
	SceneRenderPassC(
		Renderer& renderer,
		Framebuffer* target,
		const Color& clearColor,
		Scene& scene,
		const Viewpoint* viewpoint,
		u32 materialPass) noexcept;

	/// Returns the scene viewpoint
	const Viewpoint* getViewpoint() const noexcept final
	{
		return mViewpoint;
	}

	/// Sets the scene viewpoint
	void setViewpoint(const Viewpoint* viewpoint) noexcept final
	{
		mViewpoint = viewpoint;
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

private:
	/// Executes the render pass
	void doExecute() noexcept final;

	/// The scene for this render pass call
	Scene& mScene;

	/// The viewpoint for this render pass
	const Viewpoint* mViewpoint;

	/// The material pass for this render pass
	u32 mMaterialPass = 0;
};

// End of the namespace gltut
}
