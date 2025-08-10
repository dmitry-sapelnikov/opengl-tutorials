#pragma once

// Includes
#include "engine/renderer/RenderPipeline.h"
#include "engine/scene/Scene.h"

namespace gltut
{
// Global functions
/// Creates a flat color shader
ShaderMaterialBinding* createFlatColorShader(RenderPipeline& renderPipeline) noexcept;

// End of the namespace gltut
}

