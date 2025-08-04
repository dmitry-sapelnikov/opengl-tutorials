#pragma once

// Includes
#include "engine/factory/Factory.h"
#include "engine/scene/shader/SceneShaderBinding.h"
#include "engine/scene/camera/Viewpoint.h"
#include "engine/scene/nodes/GeometryNode.h"

namespace gltut
{
//	Global classes
///	Represents a render pass of the scene
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

	///	Returns the view projection matrices for this call
	virtual const Viewpoint* getViewpoint() const noexcept = 0;

	/// Returns the clear color for the render target
	virtual const Color& getClearColor() const noexcept = 0;

	/// Sets the clear color for the render target
	virtual void setClearColor(const Color& color) noexcept = 0;

	/// Returns the material layer for this render pass
	virtual u32 getMaterialPass() const noexcept = 0;

	/// Sets the material layer for this render pass
	virtual void setMaterialPass(u32 pass) noexcept = 0;

	/// Executes the render pass
	virtual void execute() noexcept = 0;
};

// End of the namespace gltut
}
