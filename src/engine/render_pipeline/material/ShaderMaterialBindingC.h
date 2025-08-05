#pragma once

// Includes
#include "../../renderer/shader/ShaderBindingT.h"
#include "engine/render_pipeline/material/ShaderMaterialBinding.h"

namespace gltut
{
// Global classes
/// Implementation of the SceneShaderBinding interface
class ShaderMaterialBindingC final : public ShaderBindingT<ShaderMaterialBinding>
{
public:
	/// Constructor
	using ShaderBindingT<ShaderMaterialBinding>::ShaderBindingT;

	/// Updates the shader binding for a scene
	void update(const RenderGeometry* geometry) const noexcept final;
};

// End of the namespace gltut
}
