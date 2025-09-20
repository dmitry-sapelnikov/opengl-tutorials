// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/scene/Scene.h"

#include "../../graphics/shader/ShaderBindingT.h"

namespace gltut
{
// Global classes
/// Implementation of the SceneShaderBinding interface
class SceneShaderBindingC final : public ShaderBindingT<SceneShaderBinding, SceneBinding::Parameter>
{
public:
	/// Constructor
	using ShaderBindingT<SceneShaderBinding, SceneBinding::Parameter>::ShaderBindingT;

	/// Updates the shader binding for a scene
	void update(const Scene* scene) const noexcept final;

private:
	/// Update the shader for a light
	void updateLight(
		const LightNode& light,
		u32 lightInd,
		SceneBinding::Parameter position,
		SceneBinding::Parameter ambientColor,
		SceneBinding::Parameter diffuseColor,
		SceneBinding::Parameter specularColor) const noexcept;

	/// Updates light binding
	void updateLights(const Scene& scene) const;
};

// End of the namespace gltut
}
