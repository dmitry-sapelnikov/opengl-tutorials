#pragma once

// Includes
#include <vector>
#include <memory>
#include "engine/render_pipeline/passes/BasicRenderPass.h"
#include "./RenderPassT.h"

namespace gltut
{
//	Global classes

///	Represents a render pass of the scene
class BasicRenderPassC final : public RenderPassT<BasicRenderPass>
{
public:
	/// Constructor
	using RenderPassT<BasicRenderPass>::RenderPassT;

	/// Adds a geometry to the render pass
	void addGeometry(Mesh* geometry, Shader* shader) noexcept final;

private:
	/// Executes the render pass
	void doExecute() noexcept final;

	/// Explicit geometries to render
	std::vector<std::pair<Mesh*, Shader*>> mGeometries;
};

// End of the namespace gltut
}
