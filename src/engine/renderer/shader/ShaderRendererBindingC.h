#pragma once

// Includes
#include "engine/renderer/shader/ShaderRendererBinding.h"
#include "engine/renderer/viewpoint/Viewpoint.h"

#include "../../graphics/shader/ShaderBindingT.h"

namespace gltut
{
// Global classes
/// Implementation of the SceneShaderBinding interface
class ShaderRendererBindingC final : public ShaderBindingT<ShaderRendererBinding, RendererBinding::Parameter>
{
public:
	/// Constructor
	using ShaderBindingT<ShaderRendererBinding, RendererBinding::Parameter>::ShaderBindingT;

	/// Updates the shader for a viewpoint
	void update(const Viewpoint* viewpoint, float aspectRatio) const noexcept final;

	/// Updates the shader for a render geometry
	void update(const RenderGeometry* geometry) const noexcept final;
};

// End of the namespace gltut
}
