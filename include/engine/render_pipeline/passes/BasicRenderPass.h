#pragma once

// Includes
#include "engine/renderer/Renderer.h"
#include "engine/render_pipeline/passes/RenderPass.h"

namespace gltut
{
//	Global classes
/// Represents a low-level render pass that
/// can be used for direct rendering of geometries
class BasicRenderPass : public RenderPass
{
public:
	/// Adds a geometry to the render pass
	virtual void addGeometry(Mesh* geometry, Shader* shader) noexcept = 0;
};

// End of the namespace gltut
}
