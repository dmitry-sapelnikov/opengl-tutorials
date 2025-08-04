#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/render_pipeline/passes/RenderPass.h"

namespace gltut
{
//	Global classes

///	Represents a render pass of the scene
template <typename PassInterface>
class RenderPassT : public PassInterface, public NonCopyable
{
public:
	/// Constructor
	RenderPassT(
		Renderer& renderer,
		Framebuffer* target,
		const Color& clearColor) noexcept :

		mRenderer(renderer),
		mTarget(target),
		mClearColor(clearColor)
	{
	}

	/// Returns the target frame buffer for this call
	Framebuffer* getTarget() const noexcept final
	{
		return mTarget;
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

	void execute() noexcept final
	{
		mRenderer.activateFramebuffer(mTarget);
		mRenderer.clear(mClearColor);
		doExecute();
	}

private:
	/// The actual implementation of the render pass
	virtual void doExecute() noexcept = 0;

	/// The renderer for this render pass call
	Renderer& mRenderer;

	/// The target frame buffer for this render pass
	Framebuffer* mTarget;

	/// The clear color for the render target
	Color mClearColor;
};

// End of the namespace gltut
}
