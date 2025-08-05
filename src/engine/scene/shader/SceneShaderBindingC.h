#pragma once

// Includes
#include "engine/scene/Scene.h"
#include "../../renderer/shader/ShaderBindingT.h"

namespace gltut
{
// Global classes
/// Implementation of the SceneShaderBinding interface
class SceneShaderBindingC final : public ShaderBindingT<SceneShaderBinding>
{
public:
	/// Constructor
	using ShaderBindingT<SceneShaderBinding>::ShaderBindingT;

	/// Updates the shader binding for a scene
	void update(const Scene* scene) const noexcept final;

private:
	/// Update the shader for a light
	void updateLight(
		const LightNode& light,
		u32 lightInd,
		SceneShaderBinding::Parameter position,
		SceneShaderBinding::Parameter ambientColor,
		SceneShaderBinding::Parameter diffuseColor,
		SceneShaderBinding::Parameter specularColor) const noexcept;

	/// Activates the shader binding for lights in a scene
	void updateLights(const Scene& scene) const;
};

// End of the namespace gltut
}
