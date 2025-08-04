#pragma once

// Includes
#include "engine/scene/camera/Viewpoint.h"
#include "engine/render_pipeline/passes/RenderPass.h"

namespace gltut
{
//	Global classes
///	Represents a render pass of the scene
class SceneRenderPass : public RenderPass
{
public:
	///	Returns the scene viewpoint
	virtual const Viewpoint* getViewpoint() const noexcept = 0;

	///	Sets the scene viewpoint
	virtual void setViewpoint(const Viewpoint* viewpoint) noexcept = 0;

	/// Returns the material layer for this render pass
	virtual u32 getMaterialPass() const noexcept = 0;

	/// Sets the material layer for this render pass
	virtual void setMaterialPass(u32 pass) noexcept = 0;
};

// End of the namespace gltut
}
