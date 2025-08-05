#pragma once

// Includes
#include "../../renderer/shader/ShaderBindingT.h"
#include "engine/render_pipeline/viewpoint/ShaderViewpointBinding.h"

namespace gltut
{
// Global classes
/// Implementation of the SceneShaderBinding interface
class ShaderViewpointBindingC final : public ShaderBindingT<ShaderViewpointBinding>
{
public:
	/// Constructor
	using ShaderBindingT<ShaderViewpointBinding>::ShaderBindingT;

	/// Updates the shader binding for a scene
	void update(const Viewpoint* viewpoint) const noexcept final;
};

// End of the namespace gltut
}
