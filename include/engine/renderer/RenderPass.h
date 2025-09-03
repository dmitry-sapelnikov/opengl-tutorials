#pragma once

// Includes
#include "engine/math/Color.h"
#include "engine/math/Rectangle.h"
#include "engine/graphics/framebuffer/Framebuffer.h"
#include "engine/renderer/objects/RenderObject.h"
#include "engine/renderer/viewpoint/Viewpoint.h"
#include "engine/graphics/DepthFunctionType.h"

namespace gltut
{
//	Global classes
///	Represents a render pass
class RenderPass
{
public:
	/// Virtual destructor
	virtual ~RenderPass() noexcept = default;

	/// Returns the object to render
	virtual const RenderObject* getObject() const noexcept = 0;

	/**
		Returns the target frame buffer for this pass
		nullptr if the pass renders to the default (window) frame buffer
	*/
	virtual const Framebuffer* getTarget() const noexcept = 0;

	/// Returns the clear color for the render target
	virtual const Color* getClearColor() const noexcept = 0;

	/// Sets the clear color for the render target
	virtual void setClearColor(const Color* color) noexcept = 0;

	/// Returns if the depth clearing is enabled
	virtual bool isDepthCleared() const noexcept = 0;

	///	Returns the scene viewpoint
	virtual const Viewpoint* getViewpoint() const noexcept = 0;

	/// Returns the material layer for this render pass
	virtual u32 getMaterialPass() const noexcept = 0;

	/// Returns the viewport rectangle for this render pass
	virtual const Rectangle2u* getViewport() const noexcept = 0;

	/// Set the face culling state
	virtual void setFaceCulling(bool back, bool front) noexcept = 0;

	/// Returns the depth function type
	virtual DepthFunctionType getDepthFunction() const noexcept = 0;

	/// Sets the depth function type
	virtual void setDepthFunction(DepthFunctionType function) noexcept = 0;

	/// Returns if the pass is active
	virtual bool isActive() const noexcept = 0;

	/// Enables/disables the pass
	virtual void setActive(bool active) noexcept = 0;

	/// Executes the render pass
	virtual void execute() noexcept = 0;
};

// End of the namespace gltut
}
