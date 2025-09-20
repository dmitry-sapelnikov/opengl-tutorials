#pragma once

// Includes
#include "../../graphics/shader/ShaderUniformBufferBindingT.h"
#include "engine/renderer/shader/ShaderUniformBufferRendererBinding.h"
#include "engine/renderer/viewpoint/Viewpoint.h"

namespace gltut
{
// Global classes
/// Implementation of the SceneShaderBinding interface
class ShaderUniformBufferRendererBindingC final : public ShaderUniformBufferBindingT<ShaderUniformBufferRendererBinding, RendererBinding::Parameter>
{
public:
	/// Constructor
	using ShaderUniformBufferBindingT<ShaderUniformBufferRendererBinding, RendererBinding::Parameter>::ShaderUniformBufferBindingT;

	/// Updates the shader for a viewpoint
	void update(const Viewpoint* viewpoint, float aspectRatio) const noexcept final;

	/// Updates the shader for a render geometry
	void update(const RenderGeometry* geometry) const noexcept final;
};

// End of the namespace gltut
}
