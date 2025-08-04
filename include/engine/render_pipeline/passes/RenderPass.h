#pragma once

// Includes
#include "engine/math/Color.h"
#include "engine/renderer/Framebuffer.h"

namespace gltut
{
//	Global classes
///	Represents a render pass
class RenderPass
{
public:
	/// Virtual destructor
	virtual ~RenderPass() noexcept = default;

	/**
		Returns the target frame buffer for this call
		nullptr if the render pass renders to the default (window) frame buffer
	*/
	virtual const Framebuffer* getTarget() const noexcept = 0;

	/// Returns the clear color for the render target
	virtual const Color& getClearColor() const noexcept = 0;

	/// Sets the clear color for the render target
	virtual void setClearColor(const Color& color) noexcept = 0;

	/// Executes the render pass
	virtual void execute() noexcept = 0;
};

// End of the namespace gltut
}
