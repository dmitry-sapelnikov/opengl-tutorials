#pragma once

// Includes
#include "engine/scene/Scene.h"
#include "engine/renderer/Renderer.h"

namespace gltut
{
// Global functions
/// Creates a Phong shader
ShaderMaterialBinding* createPhongShader(
	Renderer& renderer,
	Scene& scene,
	u32 maxDirectionalLights,
	u32 maxPointLights,
	u32 maxSpotLights) noexcept;

// End of the namespace gltut
}

