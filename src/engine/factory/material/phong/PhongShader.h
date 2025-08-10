#pragma once

// Includes
#include "engine/scene/Scene.h"
#include "engine/renderer/RenderPipeline.h"

namespace gltut
{
// Global functions
/// Creates a Phong shader
ShaderMaterialBinding* createPhongShader(
	RenderPipeline& renderer,
	Scene& scene,
	u32 maxDirectionalLights,
	u32 maxPointLights,
	u32 maxSpotLights) noexcept;

// End of the namespace gltut
}

